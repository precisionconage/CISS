#include <stdio.h>
#include "CISS_comm.h"
#include "CISS_utils.h"
#include "CISS_json_utils.h"

#define KEY 		"AK7F3095A614484A5EBC911649BD320F72"
#define SECRET 		"9b003d4267da4e7490d4db8b552a8465"

/**
 * TODO: Perform error checking.
 * TODO: Monitor sensor_data directory and read data to send.
 * TODO: Split into functions (reading data from files, posting data to server,
		 polling for response (separate thread)).
 */


int main()
{
	#if 0
	CURL 		*handle					= 0;
	const char 	*credentials 			= KEY ":" SECRET;
	const char	*channel_URL			= "http://birol.dlinkddns.com:19090/v1/apps/ciss/stores/sensor-data/channels";
	const char	*data_URL				= "http://birol.dlinkddns.com:19090/v1/apps/ciss/data/sensor-data";
	server_response		rx_buf			= {0};
	CURLcode 			result			= 0;
	struct curl_slist	*headers		= NULL;
	#endif
	int inotifyFd = inotify_init();
	char filename[NAME_BUF_SIZE];
	char sensor[NAME_BUF_SIZE];
	char timestamp[NAME_BUF_SIZE];
	json_object *server_JSON;
	
	CISS_read_filename("./testdir", filename, inotifyFd);
	CISS_parse_filename(filename, sensor, timestamp);
	CISS_delete_file("testdir/", filename);
	server_JSON = CISS_create_reading_JSON(sensor, timestamp, 100, "devices/ciss-I/_mac/0x298493429348329");
	printf("The JSON:\n\n %s\n", json_object_to_json_string(server_JSON));
	
	#if 0
	curl_slist_free_all(headers);
	curl_easy_cleanup(handle);
	#endif

	return 0;
}

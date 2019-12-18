#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ingest {int /*<<< orphan*/  url; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  bstrdup (char*) ; 
 int /*<<< orphan*/  cur_ingests ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct ingest*) ; 
 int /*<<< orphan*/  ingests_loaded ; 
 int load_ingests (char*,int) ; 
 int /*<<< orphan*/  mutex ; 
 char* obs_module_config_path (char*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 scalar_t__ os_file_exists (char*) ; 
 char* os_quick_read_utf8_file (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void load_twitch_data(void)
{
	char *twitch_cache = obs_module_config_path("twitch_ingests.json");

	struct ingest def = {.name = bstrdup("Default"),
			     .url = bstrdup("rtmp://live.twitch.tv/app")};

	pthread_mutex_lock(&mutex);
	da_push_back(cur_ingests, &def);
	pthread_mutex_unlock(&mutex);

	if (os_file_exists(twitch_cache)) {
		char *data = os_quick_read_utf8_file(twitch_cache);
		bool success;

		pthread_mutex_lock(&mutex);
		success = load_ingests(data, false);
		pthread_mutex_unlock(&mutex);

		if (success) {
			os_atomic_set_bool(&ingests_loaded, true);
		}

		bfree(data);
	}

	bfree(twitch_cache);
}
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

/* Variables and functions */
 int /*<<< orphan*/  get_module_name () ; 
 int /*<<< orphan*/  ingests_loaded ; 
 int /*<<< orphan*/  ingests_refreshed ; 
 int /*<<< orphan*/  ingests_refreshing ; 
 scalar_t__ os_atomic_load_bool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_sleep_ms (int) ; 
 int /*<<< orphan*/  twitch_ingest_update ; 
 int /*<<< orphan*/  twitch_update_info ; 
 int /*<<< orphan*/  update_info_create_single (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void twitch_ingests_refresh(int seconds)
{
	if (os_atomic_load_bool(&ingests_refreshed))
		return;

	if (!os_atomic_load_bool(&ingests_refreshing)) {
		os_atomic_set_bool(&ingests_refreshing, true);

		twitch_update_info = update_info_create_single(
			"[twitch ingest update] ", get_module_name(),
			"https://ingest.twitch.tv/api/v2/ingests",
			twitch_ingest_update, NULL);
	}

	/* wait five seconds max when loading ingests for the first time */
	if (!os_atomic_load_bool(&ingests_loaded)) {
		for (int i = 0; i < seconds * 100; i++) {
			if (os_atomic_load_bool(&ingests_refreshed)) {
				break;
			}
			os_sleep_ms(10);
		}
	}
}
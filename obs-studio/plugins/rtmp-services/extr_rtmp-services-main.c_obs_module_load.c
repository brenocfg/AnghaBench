#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  proc_handler_t ;
struct TYPE_4__ {int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTMP_SERVICES_LOG_STR ; 
 int /*<<< orphan*/  RTMP_SERVICES_URL ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  confirm_service_file ; 
 int /*<<< orphan*/  dstr_cat (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dstr_copy (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  init_twitch_data () ; 
 int /*<<< orphan*/  load_twitch_data () ; 
 TYPE_1__ module_name ; 
 int /*<<< orphan*/ * obs_get_proc_handler () ; 
 char* obs_get_version_string () ; 
 char* obs_module_config_path (char*) ; 
 char* obs_module_file (char*) ; 
 int /*<<< orphan*/  obs_register_service (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_handler_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refresh_callback ; 
 int /*<<< orphan*/  rtmp_common_service ; 
 int /*<<< orphan*/  rtmp_custom_service ; 
 int /*<<< orphan*/  update_info ; 
 int /*<<< orphan*/  update_info_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool obs_module_load(void)
{
	init_twitch_data();

	dstr_copy(&module_name, "rtmp-services plugin (libobs ");
	dstr_cat(&module_name, obs_get_version_string());
	dstr_cat(&module_name, ")");

	proc_handler_t *ph = obs_get_proc_handler();
	proc_handler_add(ph, "void twitch_ingests_refresh(int seconds)",
			 refresh_callback, NULL);

#if !defined(_WIN32) || CHECK_FOR_SERVICE_UPDATES
	char *local_dir = obs_module_file("");
	char *cache_dir = obs_module_config_path("");

	if (cache_dir) {
		update_info = update_info_create(RTMP_SERVICES_LOG_STR,
						 module_name.array,
						 RTMP_SERVICES_URL, local_dir,
						 cache_dir,
						 confirm_service_file, NULL);
	}

	load_twitch_data();

	bfree(local_dir);
	bfree(cache_dir);
#endif

	obs_register_service(&rtmp_common_service);
	obs_register_service(&rtmp_custom_service);
	return true;
}
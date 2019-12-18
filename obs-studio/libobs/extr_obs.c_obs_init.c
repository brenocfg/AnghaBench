#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct obs_core {int dummy; } ;
typedef  int /*<<< orphan*/  profiler_name_store_t ;
struct TYPE_5__ {int /*<<< orphan*/  gpu_encoder_mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  monitoring_mutex; } ;
struct TYPE_7__ {int name_store_owned; void* locale; void* module_config_path; int /*<<< orphan*/ * name_store; TYPE_1__ video; TYPE_2__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  add_default_module_paths () ; 
 int /*<<< orphan*/  audio_line_info ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 void* bstrdup (char const*) ; 
 TYPE_3__* bzalloc (int) ; 
 int /*<<< orphan*/  group_info ; 
 int /*<<< orphan*/  log_system_info () ; 
 TYPE_3__* obs ; 
 int /*<<< orphan*/  obs_init_data () ; 
 int /*<<< orphan*/  obs_init_handlers () ; 
 int /*<<< orphan*/  obs_init_hotkeys () ; 
 int /*<<< orphan*/  obs_register_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * profiler_name_store_create () ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scene_info ; 

__attribute__((used)) static bool obs_init(const char *locale, const char *module_config_path,
		     profiler_name_store_t *store)
{
	obs = bzalloc(sizeof(struct obs_core));

	pthread_mutex_init_value(&obs->audio.monitoring_mutex);
	pthread_mutex_init_value(&obs->video.gpu_encoder_mutex);

	obs->name_store_owned = !store;
	obs->name_store = store ? store : profiler_name_store_create();
	if (!obs->name_store) {
		blog(LOG_ERROR, "Couldn't create profiler name store");
		return false;
	}

	log_system_info();

	if (!obs_init_data())
		return false;
	if (!obs_init_handlers())
		return false;
	if (!obs_init_hotkeys())
		return false;

	if (module_config_path)
		obs->module_config_path = bstrdup(module_config_path);
	obs->locale = bstrdup(locale);
	obs_register_source(&scene_info);
	obs_register_source(&group_info);
	obs_register_source(&audio_line_info);
	add_default_module_paths();
	return true;
}
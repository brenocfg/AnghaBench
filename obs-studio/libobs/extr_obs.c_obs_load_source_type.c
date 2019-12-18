#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_22__ {int default_flags; int /*<<< orphan*/ * private_settings; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;
typedef  scalar_t__ int64_t ;
typedef  enum obs_monitoring_type { ____Placeholder_obs_monitoring_type } obs_monitoring_type ;
typedef  enum obs_deinterlace_mode { ____Placeholder_obs_deinterlace_mode } obs_deinterlace_mode ;
typedef  enum obs_deinterlace_field_order { ____Placeholder_obs_deinterlace_field_order } obs_deinterlace_field_order ;

/* Variables and functions */
 scalar_t__ MAKE_SEMANTIC_VERSION (int,int,int) ; 
 int OBS_MONITORING_TYPE_MONITOR_ONLY ; 
 scalar_t__ OBS_SOURCE_MONITOR_BY_DEFAULT ; 
 size_t obs_data_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_array_item (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_create () ; 
 int /*<<< orphan*/ * obs_data_get_array (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 double obs_data_get_double (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 void* obs_data_get_obj (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_default_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_data_set_default_double (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__* obs_source_create_set_last_ver (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  obs_source_enable_push_to_mute (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_enable_push_to_talk (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_filter_add (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ obs_source_get_output_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_source_release (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_source_set_audio_mixers (TYPE_1__*,int) ; 
 int /*<<< orphan*/  obs_source_set_balance_value (TYPE_1__*,float) ; 
 int /*<<< orphan*/  obs_source_set_deinterlace_field_order (TYPE_1__*,int) ; 
 int /*<<< orphan*/  obs_source_set_deinterlace_mode (TYPE_1__*,int) ; 
 int /*<<< orphan*/  obs_source_set_enabled (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_set_flags (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  obs_source_set_monitoring_type (TYPE_1__*,int) ; 
 int /*<<< orphan*/  obs_source_set_muted (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_set_push_to_mute_delay (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  obs_source_set_push_to_talk_delay (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  obs_source_set_sync_offset (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  obs_source_set_volume (TYPE_1__*,float) ; 

__attribute__((used)) static obs_source_t *obs_load_source_type(obs_data_t *source_data)
{
	obs_data_array_t *filters = obs_data_get_array(source_data, "filters");
	obs_source_t *source;
	const char *name = obs_data_get_string(source_data, "name");
	const char *id = obs_data_get_string(source_data, "id");
	obs_data_t *settings = obs_data_get_obj(source_data, "settings");
	obs_data_t *hotkeys = obs_data_get_obj(source_data, "hotkeys");
	double volume;
	double balance;
	int64_t sync;
	uint32_t prev_ver;
	uint32_t caps;
	uint32_t flags;
	uint32_t mixers;
	int di_order;
	int di_mode;
	int monitoring_type;

	prev_ver = (uint32_t)obs_data_get_int(source_data, "prev_ver");

	source = obs_source_create_set_last_ver(id, name, settings, hotkeys,
						prev_ver);

	obs_data_release(hotkeys);

	caps = obs_source_get_output_flags(source);

	obs_data_set_default_double(source_data, "volume", 1.0);
	volume = obs_data_get_double(source_data, "volume");
	obs_source_set_volume(source, (float)volume);

	obs_data_set_default_double(source_data, "balance", 0.5);
	balance = obs_data_get_double(source_data, "balance");
	obs_source_set_balance_value(source, (float)balance);

	sync = obs_data_get_int(source_data, "sync");
	obs_source_set_sync_offset(source, sync);

	obs_data_set_default_int(source_data, "mixers", 0x3F);
	mixers = (uint32_t)obs_data_get_int(source_data, "mixers");
	obs_source_set_audio_mixers(source, mixers);

	obs_data_set_default_int(source_data, "flags", source->default_flags);
	flags = (uint32_t)obs_data_get_int(source_data, "flags");
	obs_source_set_flags(source, flags);

	obs_data_set_default_bool(source_data, "enabled", true);
	obs_source_set_enabled(source,
			       obs_data_get_bool(source_data, "enabled"));

	obs_data_set_default_bool(source_data, "muted", false);
	obs_source_set_muted(source, obs_data_get_bool(source_data, "muted"));

	obs_data_set_default_bool(source_data, "push-to-mute", false);
	obs_source_enable_push_to_mute(
		source, obs_data_get_bool(source_data, "push-to-mute"));

	obs_data_set_default_int(source_data, "push-to-mute-delay", 0);
	obs_source_set_push_to_mute_delay(
		source, obs_data_get_int(source_data, "push-to-mute-delay"));

	obs_data_set_default_bool(source_data, "push-to-talk", false);
	obs_source_enable_push_to_talk(
		source, obs_data_get_bool(source_data, "push-to-talk"));

	obs_data_set_default_int(source_data, "push-to-talk-delay", 0);
	obs_source_set_push_to_talk_delay(
		source, obs_data_get_int(source_data, "push-to-talk-delay"));

	di_mode = (int)obs_data_get_int(source_data, "deinterlace_mode");
	obs_source_set_deinterlace_mode(source,
					(enum obs_deinterlace_mode)di_mode);

	di_order =
		(int)obs_data_get_int(source_data, "deinterlace_field_order");
	obs_source_set_deinterlace_field_order(
		source, (enum obs_deinterlace_field_order)di_order);

	monitoring_type = (int)obs_data_get_int(source_data, "monitoring_type");
	if (prev_ver < MAKE_SEMANTIC_VERSION(23, 2, 2)) {
		if ((caps & OBS_SOURCE_MONITOR_BY_DEFAULT) != 0) {
			/* updates older sources to enable monitoring
			 * automatically if they added monitoring by default in
			 * version 24 */
			monitoring_type = OBS_MONITORING_TYPE_MONITOR_ONLY;
			obs_source_set_audio_mixers(source, 0x3F);
		}
	}
	obs_source_set_monitoring_type(
		source, (enum obs_monitoring_type)monitoring_type);

	obs_data_release(source->private_settings);
	source->private_settings =
		obs_data_get_obj(source_data, "private_settings");
	if (!source->private_settings)
		source->private_settings = obs_data_create();

	if (filters) {
		size_t count = obs_data_array_count(filters);

		for (size_t i = 0; i < count; i++) {
			obs_data_t *filter_data =
				obs_data_array_item(filters, i);

			obs_source_t *filter =
				obs_load_source_type(filter_data);
			if (filter) {
				obs_source_filter_add(source, filter);
				obs_source_release(filter);
			}

			obs_data_release(filter_data);
		}

		obs_data_array_release(filters);
	}

	obs_data_release(settings);

	return source;
}
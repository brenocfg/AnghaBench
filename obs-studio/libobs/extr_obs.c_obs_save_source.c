#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_28__ {size_t num; TYPE_4__** array; } ;
struct TYPE_27__ {scalar_t__ type; } ;
struct TYPE_26__ {int /*<<< orphan*/ * hotkey_data; } ;
struct TYPE_29__ {int /*<<< orphan*/  filter_mutex; TYPE_3__ filters; TYPE_2__ info; int /*<<< orphan*/ * private_settings; TYPE_1__ context; } ;
typedef  TYPE_4__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;
typedef  int int64_t ;

/* Variables and functions */
 int LIBOBS_API_VER ; 
 scalar_t__ OBS_SOURCE_TYPE_TRANSITION ; 
 int /*<<< orphan*/ * obs_data_array_create () ; 
 int /*<<< orphan*/  obs_data_array_push_back (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_create () ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_data_set_double (int /*<<< orphan*/ *,char*,float) ; 
 int /*<<< orphan*/  obs_data_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_data_set_obj (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * obs_hotkeys_save_source (TYPE_4__*) ; 
 int obs_source_enabled (TYPE_4__*) ; 
 int obs_source_get_audio_mixers (TYPE_4__*) ; 
 float obs_source_get_balance_value (TYPE_4__*) ; 
 scalar_t__ obs_source_get_deinterlace_field_order (TYPE_4__*) ; 
 scalar_t__ obs_source_get_deinterlace_mode (TYPE_4__*) ; 
 int obs_source_get_flags (TYPE_4__*) ; 
 char* obs_source_get_id (TYPE_4__*) ; 
 scalar_t__ obs_source_get_monitoring_type (TYPE_4__*) ; 
 char* obs_source_get_name (TYPE_4__*) ; 
 int obs_source_get_push_to_mute_delay (TYPE_4__*) ; 
 int obs_source_get_push_to_talk_delay (TYPE_4__*) ; 
 int /*<<< orphan*/ * obs_source_get_settings (TYPE_4__*) ; 
 int obs_source_get_sync_offset (TYPE_4__*) ; 
 float obs_source_get_volume (TYPE_4__*) ; 
 int obs_source_muted (TYPE_4__*) ; 
 int obs_source_push_to_mute_enabled (TYPE_4__*) ; 
 int obs_source_push_to_talk_enabled (TYPE_4__*) ; 
 int /*<<< orphan*/  obs_source_save (TYPE_4__*) ; 
 int /*<<< orphan*/  obs_transition_save (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

obs_data_t *obs_save_source(obs_source_t *source)
{
	obs_data_array_t *filters = obs_data_array_create();
	obs_data_t *source_data = obs_data_create();
	obs_data_t *settings = obs_source_get_settings(source);
	obs_data_t *hotkey_data = source->context.hotkey_data;
	obs_data_t *hotkeys;
	float volume = obs_source_get_volume(source);
	float balance = obs_source_get_balance_value(source);
	uint32_t mixers = obs_source_get_audio_mixers(source);
	int64_t sync = obs_source_get_sync_offset(source);
	uint32_t flags = obs_source_get_flags(source);
	const char *name = obs_source_get_name(source);
	const char *id = obs_source_get_id(source);
	bool enabled = obs_source_enabled(source);
	bool muted = obs_source_muted(source);
	bool push_to_mute = obs_source_push_to_mute_enabled(source);
	uint64_t ptm_delay = obs_source_get_push_to_mute_delay(source);
	bool push_to_talk = obs_source_push_to_talk_enabled(source);
	uint64_t ptt_delay = obs_source_get_push_to_talk_delay(source);
	int m_type = (int)obs_source_get_monitoring_type(source);
	int di_mode = (int)obs_source_get_deinterlace_mode(source);
	int di_order = (int)obs_source_get_deinterlace_field_order(source);

	obs_source_save(source);
	hotkeys = obs_hotkeys_save_source(source);

	if (hotkeys) {
		obs_data_release(hotkey_data);
		source->context.hotkey_data = hotkeys;
		hotkey_data = hotkeys;
	}

	obs_data_set_int(source_data, "prev_ver", LIBOBS_API_VER);

	obs_data_set_string(source_data, "name", name);
	obs_data_set_string(source_data, "id", id);
	obs_data_set_obj(source_data, "settings", settings);
	obs_data_set_int(source_data, "mixers", mixers);
	obs_data_set_int(source_data, "sync", sync);
	obs_data_set_int(source_data, "flags", flags);
	obs_data_set_double(source_data, "volume", volume);
	obs_data_set_double(source_data, "balance", balance);
	obs_data_set_bool(source_data, "enabled", enabled);
	obs_data_set_bool(source_data, "muted", muted);
	obs_data_set_bool(source_data, "push-to-mute", push_to_mute);
	obs_data_set_int(source_data, "push-to-mute-delay", ptm_delay);
	obs_data_set_bool(source_data, "push-to-talk", push_to_talk);
	obs_data_set_int(source_data, "push-to-talk-delay", ptt_delay);
	obs_data_set_obj(source_data, "hotkeys", hotkey_data);
	obs_data_set_int(source_data, "deinterlace_mode", di_mode);
	obs_data_set_int(source_data, "deinterlace_field_order", di_order);
	obs_data_set_int(source_data, "monitoring_type", m_type);

	obs_data_set_obj(source_data, "private_settings",
			 source->private_settings);

	if (source->info.type == OBS_SOURCE_TYPE_TRANSITION)
		obs_transition_save(source, source_data);

	pthread_mutex_lock(&source->filter_mutex);

	if (source->filters.num) {
		for (size_t i = source->filters.num; i > 0; i--) {
			obs_source_t *filter = source->filters.array[i - 1];
			obs_data_t *filter_data = obs_save_source(filter);
			obs_data_array_push_back(filters, filter_data);
			obs_data_release(filter_data);
		}

		obs_data_set_array(source_data, "filters", filters);
	}

	pthread_mutex_unlock(&source->filter_mutex);

	obs_data_release(settings);
	obs_data_array_release(filters);

	return source_data;
}
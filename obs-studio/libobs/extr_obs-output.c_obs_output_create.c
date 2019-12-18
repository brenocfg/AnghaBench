#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct obs_output_info {int /*<<< orphan*/  (* create ) (int /*<<< orphan*/ ,struct obs_output*) ;int /*<<< orphan*/  (* get_defaults ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; int /*<<< orphan*/  settings; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct obs_output {int owns_info_id; int reconnect_retry_sec; int reconnect_retry_max; int valid; TYPE_4__ context; TYPE_2__* control; int /*<<< orphan*/  reconnect_stop_event; struct obs_output_info info; int /*<<< orphan*/  audio; int /*<<< orphan*/  video; int /*<<< orphan*/  stopping_event; TYPE_1__ pause; int /*<<< orphan*/  caption_mutex; int /*<<< orphan*/  delay_mutex; int /*<<< orphan*/  interleaved_mutex; } ;
typedef  int /*<<< orphan*/  obs_weak_output_t ;
typedef  struct obs_output obs_output_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
struct TYPE_8__ {int /*<<< orphan*/  first_output; int /*<<< orphan*/  outputs_mutex; } ;
struct TYPE_10__ {TYPE_3__ data; } ;
struct TYPE_7__ {struct obs_output* output; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  OS_EVENT_TYPE_MANUAL ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  bstrdup (char const*) ; 
 void* bzalloc (int) ; 
 struct obs_output_info* find_output (char const*) ; 
 int /*<<< orphan*/  init_output_handlers (struct obs_output*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* obs ; 
 int /*<<< orphan*/  obs_context_data_insert (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_get_audio () ; 
 int /*<<< orphan*/  obs_get_video () ; 
 int /*<<< orphan*/  obs_output_destroy (struct obs_output*) ; 
 int os_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct obs_output*) ; 

obs_output_t *obs_output_create(const char *id, const char *name,
				obs_data_t *settings, obs_data_t *hotkey_data)
{
	const struct obs_output_info *info = find_output(id);
	struct obs_output *output;
	int ret;

	output = bzalloc(sizeof(struct obs_output));
	pthread_mutex_init_value(&output->interleaved_mutex);
	pthread_mutex_init_value(&output->delay_mutex);
	pthread_mutex_init_value(&output->caption_mutex);
	pthread_mutex_init_value(&output->pause.mutex);

	if (pthread_mutex_init(&output->interleaved_mutex, NULL) != 0)
		goto fail;
	if (pthread_mutex_init(&output->delay_mutex, NULL) != 0)
		goto fail;
	if (pthread_mutex_init(&output->caption_mutex, NULL) != 0)
		goto fail;
	if (pthread_mutex_init(&output->pause.mutex, NULL) != 0)
		goto fail;
	if (os_event_init(&output->stopping_event, OS_EVENT_TYPE_MANUAL) != 0)
		goto fail;
	if (!init_output_handlers(output, name, settings, hotkey_data))
		goto fail;

	os_event_signal(output->stopping_event);

	if (!info) {
		blog(LOG_ERROR, "Output ID '%s' not found", id);

		output->info.id = bstrdup(id);
		output->owns_info_id = true;
	} else {
		output->info = *info;
	}
	output->video = obs_get_video();
	output->audio = obs_get_audio();
	if (output->info.get_defaults)
		output->info.get_defaults(output->context.settings);

	ret = os_event_init(&output->reconnect_stop_event,
			    OS_EVENT_TYPE_MANUAL);
	if (ret < 0)
		goto fail;

	output->reconnect_retry_sec = 2;
	output->reconnect_retry_max = 20;
	output->valid = true;

	output->control = bzalloc(sizeof(obs_weak_output_t));
	output->control->output = output;

	obs_context_data_insert(&output->context, &obs->data.outputs_mutex,
				&obs->data.first_output);

	if (info)
		output->context.data =
			info->create(output->context.settings, output);
	if (!output->context.data)
		blog(LOG_ERROR, "Failed to create output '%s'!", name);

	blog(LOG_DEBUG, "output '%s' (%s) created", name, id);
	return output;

fail:
	obs_output_destroy(output);
	return NULL;
}
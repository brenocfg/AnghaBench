#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct obs_view {int /*<<< orphan*/  channels_mutex; struct obs_source** channels; } ;
struct obs_source {int dummy; } ;
struct calldata {int /*<<< orphan*/  member_0; } ;
typedef  struct obs_source obs_source_t ;
struct TYPE_3__ {struct obs_view main_view; } ;
struct TYPE_4__ {int /*<<< orphan*/  signals; TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAIN_VIEW ; 
 size_t MAX_CHANNELS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  calldata_free (struct calldata*) ; 
 int /*<<< orphan*/  calldata_get_ptr (struct calldata*,char*,struct obs_source**) ; 
 int /*<<< orphan*/  calldata_set_int (struct calldata*,char*,size_t) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,struct obs_source*) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  obs_source_activate (struct obs_source*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_addref (struct obs_source*) ; 
 int /*<<< orphan*/  obs_source_deactivate (struct obs_source*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_release (struct obs_source*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 

void obs_set_output_source(uint32_t channel, obs_source_t *source)
{
	assert(channel < MAX_CHANNELS);

	if (!obs)
		return;
	if (channel >= MAX_CHANNELS)
		return;

	struct obs_source *prev_source;
	struct obs_view *view = &obs->data.main_view;
	struct calldata params = {0};

	pthread_mutex_lock(&view->channels_mutex);

	obs_source_addref(source);

	prev_source = view->channels[channel];

	calldata_set_int(&params, "channel", channel);
	calldata_set_ptr(&params, "prev_source", prev_source);
	calldata_set_ptr(&params, "source", source);
	signal_handler_signal(obs->signals, "channel_change", &params);
	calldata_get_ptr(&params, "source", &source);
	calldata_free(&params);

	view->channels[channel] = source;

	pthread_mutex_unlock(&view->channels_mutex);

	if (source)
		obs_source_activate(source, MAIN_VIEW);

	if (prev_source) {
		obs_source_deactivate(prev_source, MAIN_VIEW);
		obs_source_release(prev_source);
	}
}
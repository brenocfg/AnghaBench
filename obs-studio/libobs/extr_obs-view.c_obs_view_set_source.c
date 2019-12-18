#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct obs_source {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  channels_mutex; struct obs_source** channels; } ;
typedef  TYPE_1__ obs_view_t ;
typedef  struct obs_source obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_VIEW ; 
 size_t MAX_CHANNELS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  obs_source_activate (struct obs_source*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_addref (struct obs_source*) ; 
 int /*<<< orphan*/  obs_source_deactivate (struct obs_source*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_release (struct obs_source*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_view_set_source(obs_view_t *view, uint32_t channel,
			 obs_source_t *source)
{
	struct obs_source *prev_source;

	assert(channel < MAX_CHANNELS);

	if (!view)
		return;
	if (channel >= MAX_CHANNELS)
		return;

	pthread_mutex_lock(&view->channels_mutex);

	obs_source_addref(source);

	prev_source = view->channels[channel];
	view->channels[channel] = source;

	pthread_mutex_unlock(&view->channels_mutex);

	if (source)
		obs_source_activate(source, AUX_VIEW);

	if (prev_source) {
		obs_source_deactivate(prev_source, AUX_VIEW);
		obs_source_release(prev_source);
	}
}
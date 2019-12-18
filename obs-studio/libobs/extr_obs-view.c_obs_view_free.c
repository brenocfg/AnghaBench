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
struct obs_view {int /*<<< orphan*/  channels_mutex; struct obs_source** channels; } ;
struct obs_source {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_VIEW ; 
 size_t MAX_CHANNELS ; 
 int /*<<< orphan*/  memset (struct obs_source**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_source_deactivate (struct obs_source*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_release (struct obs_source*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void obs_view_free(struct obs_view *view)
{
	if (!view)
		return;

	for (size_t i = 0; i < MAX_CHANNELS; i++) {
		struct obs_source *source = view->channels[i];
		if (source) {
			obs_source_deactivate(source, AUX_VIEW);
			obs_source_release(source);
		}
	}

	memset(view->channels, 0, sizeof(view->channels));
	pthread_mutex_destroy(&view->channels_mutex);
}
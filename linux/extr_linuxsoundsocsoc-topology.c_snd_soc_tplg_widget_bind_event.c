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
typedef  scalar_t__ u16 ;
struct snd_soc_tplg_widget_events {scalar_t__ type; int /*<<< orphan*/ * event_handler; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 int EINVAL ; 

int snd_soc_tplg_widget_bind_event(struct snd_soc_dapm_widget *w,
		const struct snd_soc_tplg_widget_events *events,
		int num_events, u16 event_type)
{
	int i;

	w->event = NULL;

	for (i = 0; i < num_events; i++) {
		if (event_type == events[i].type) {

			/* found - so assign event */
			w->event = events[i].event_handler;
			return 0;
		}
	}

	/* not found */
	return -EINVAL;
}
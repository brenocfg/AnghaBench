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
struct synth_event {scalar_t__ ref; } ;
struct dyn_event {int dummy; } ;

/* Variables and functions */
 struct synth_event* to_synth_event (struct dyn_event*) ; 

__attribute__((used)) static bool synth_event_is_busy(struct dyn_event *ev)
{
	struct synth_event *event = to_synth_event(ev);

	return event->ref != 0;
}
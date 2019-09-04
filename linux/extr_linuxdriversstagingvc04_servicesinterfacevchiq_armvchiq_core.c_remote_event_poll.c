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
typedef  int /*<<< orphan*/  VCHIQ_STATE_T ;
struct TYPE_4__ {scalar_t__ armed; scalar_t__ fired; } ;
typedef  TYPE_1__ REMOTE_EVENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  remote_event_signal_local (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static inline void
remote_event_poll(VCHIQ_STATE_T *state, REMOTE_EVENT_T *event)
{
	if (event->fired && event->armed)
		remote_event_signal_local(state, event);
}
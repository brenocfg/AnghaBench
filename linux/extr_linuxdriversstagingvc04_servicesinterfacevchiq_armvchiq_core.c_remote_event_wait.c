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
struct semaphore {int dummy; } ;
typedef  int /*<<< orphan*/  VCHIQ_STATE_T ;
struct TYPE_3__ {int armed; int event; scalar_t__ fired; } ;
typedef  TYPE_1__ REMOTE_EVENT_T ;

/* Variables and functions */
 scalar_t__ down_interruptible (struct semaphore*) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sy ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline int
remote_event_wait(VCHIQ_STATE_T *state, REMOTE_EVENT_T *event)
{
	if (!event->fired) {
		event->armed = 1;
		dsb(sy);
		if (!event->fired) {
			if (down_interruptible(
					(struct semaphore *)
					((char *)state + event->event)) != 0) {
				event->armed = 0;
				return 0;
			}
		}
		event->armed = 0;
		wmb();
	}

	event->fired = 0;
	return 1;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct rsi_event {int /*<<< orphan*/  event_condition; int /*<<< orphan*/  event_queue; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int rsi_wait_event(struct rsi_event *event, u32 timeout)
{
	int status = 0;

	if (!timeout)
		status = wait_event_interruptible(event->event_queue,
				(atomic_read(&event->event_condition) == 0));
	else
		status = wait_event_interruptible_timeout(event->event_queue,
				(atomic_read(&event->event_condition) == 0),
				timeout);
	return status;
}
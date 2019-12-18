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
struct file {struct eventpoll* private_data; } ;
struct eventpoll {int /*<<< orphan*/  poll_wait; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  ep_read_events_proc ; 
 int /*<<< orphan*/  ep_scan_ready_list (struct eventpoll*,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t ep_eventpoll_poll(struct file *file, poll_table *wait)
{
	struct eventpoll *ep = file->private_data;
	int depth = 0;

	/* Insert inside our poll wait queue */
	poll_wait(file, &ep->poll_wait, wait);

	/*
	 * Proceed to find out if wanted events are really available inside
	 * the ready list.
	 */
	return ep_scan_ready_list(ep, ep_read_events_proc,
				  &depth, depth, false);
}
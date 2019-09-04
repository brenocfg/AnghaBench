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
struct ctl_table_poll {int /*<<< orphan*/  wait; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void proc_sys_poll_notify(struct ctl_table_poll *poll)
{
	if (!poll)
		return;

	atomic_inc(&poll->event);
	wake_up_interruptible(&poll->wait);
}
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
struct gb_loopback {scalar_t__ outstanding_operations_max; int /*<<< orphan*/  outstanding_operations; int /*<<< orphan*/  wq_completion; scalar_t__ async; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gb_loopback_async_wait_to_send(struct gb_loopback *gb)
{
	if (!(gb->async && gb->outstanding_operations_max))
		return;
	wait_event_interruptible(gb->wq_completion,
				 (atomic_read(&gb->outstanding_operations) <
				  gb->outstanding_operations_max) ||
				  kthread_should_stop());
}
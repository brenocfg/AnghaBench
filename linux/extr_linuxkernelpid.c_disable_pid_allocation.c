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
struct pid_namespace {int /*<<< orphan*/  pid_allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDNS_ADDING ; 
 int /*<<< orphan*/  pidmap_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void disable_pid_allocation(struct pid_namespace *ns)
{
	spin_lock_irq(&pidmap_lock);
	ns->pid_allocated &= ~PIDNS_ADDING;
	spin_unlock_irq(&pidmap_lock);
}
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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*) ; 
 int HZ ; 
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_bus_type ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  recovery_check ; 
 int* recovery_delay ; 
 int /*<<< orphan*/  recovery_lock ; 
 int recovery_phase ; 
 int /*<<< orphan*/  recovery_timer ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recovery_work_func(struct work_struct *unused)
{
	int redo = 0;

	bus_for_each_dev(&ccw_bus_type, NULL, &redo, recovery_check);
	if (redo) {
		spin_lock_irq(&recovery_lock);
		if (!timer_pending(&recovery_timer)) {
			if (recovery_phase < ARRAY_SIZE(recovery_delay) - 1)
				recovery_phase++;
			mod_timer(&recovery_timer, jiffies +
				  recovery_delay[recovery_phase] * HZ);
		}
		spin_unlock_irq(&recovery_lock);
	} else
		CIO_MSG_EVENT(3, "recovery: end\n");
}
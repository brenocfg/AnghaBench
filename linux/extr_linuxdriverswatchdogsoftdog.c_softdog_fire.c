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
struct hrtimer {int dummy; } ;
typedef  enum hrtimer_restart { ____Placeholder_hrtimer_restart } hrtimer_restart ;

/* Variables and functions */
 int HRTIMER_NORESTART ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  emergency_restart () ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 scalar_t__ soft_noboot ; 
 scalar_t__ soft_panic ; 

__attribute__((used)) static enum hrtimer_restart softdog_fire(struct hrtimer *timer)
{
	module_put(THIS_MODULE);
	if (soft_noboot) {
		pr_crit("Triggered - Reboot ignored\n");
	} else if (soft_panic) {
		pr_crit("Initiating panic\n");
		panic("Software Watchdog Timer expired");
	} else {
		pr_crit("Initiating system reboot\n");
		emergency_restart();
		pr_crit("Reboot didn't ?????\n");
	}

	return HRTIMER_NORESTART;
}
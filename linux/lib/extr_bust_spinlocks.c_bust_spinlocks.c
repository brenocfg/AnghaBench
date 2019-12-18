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

/* Variables and functions */
 int /*<<< orphan*/  console_unblank () ; 
 scalar_t__ oops_in_progress ; 
 int /*<<< orphan*/  unblank_screen () ; 
 int /*<<< orphan*/  wake_up_klogd () ; 

void bust_spinlocks(int yes)
{
	if (yes) {
		++oops_in_progress;
	} else {
#ifdef CONFIG_VT
		unblank_screen();
#endif
		console_unblank();
		if (--oops_in_progress == 0)
			wake_up_klogd();
	}
}
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
 int on_commit_launcher_wakeup ; 

void
ApplyLauncherWakeupAtCommit(void)
{
	if (!on_commit_launcher_wakeup)
		on_commit_launcher_wakeup = true;
}
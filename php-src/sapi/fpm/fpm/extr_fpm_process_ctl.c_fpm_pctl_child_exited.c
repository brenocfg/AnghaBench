#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  running_children; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_PCTL_ACTION_LAST_CHILD_EXITED ; 
 scalar_t__ FPM_PCTL_STATE_NORMAL ; 
 int /*<<< orphan*/  FPM_PCTL_STATE_UNSPECIFIED ; 
 TYPE_1__ fpm_globals ; 
 int /*<<< orphan*/  fpm_pctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_state ; 

int fpm_pctl_child_exited() /* {{{ */
{
	if (fpm_state == FPM_PCTL_STATE_NORMAL) {
		return 0;
	}

	if (!fpm_globals.running_children) {
		fpm_pctl(FPM_PCTL_STATE_UNSPECIFIED, FPM_PCTL_ACTION_LAST_CHILD_EXITED);
	}
	return 0;
}
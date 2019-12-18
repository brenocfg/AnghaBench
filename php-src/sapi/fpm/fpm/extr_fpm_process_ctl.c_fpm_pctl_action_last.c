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
#define  FPM_PCTL_STATE_FINISHING 130 
#define  FPM_PCTL_STATE_RELOADING 129 
#define  FPM_PCTL_STATE_TERMINATING 128 
 int /*<<< orphan*/  fpm_pctl_exec () ; 
 int /*<<< orphan*/  fpm_pctl_exit () ; 
 int fpm_state ; 

__attribute__((used)) static void fpm_pctl_action_last() /* {{{ */
{
	switch (fpm_state) {
		case FPM_PCTL_STATE_RELOADING:
			fpm_pctl_exec();
			break;

		case FPM_PCTL_STATE_FINISHING:
		case FPM_PCTL_STATE_TERMINATING:
			fpm_pctl_exit();
			break;
	}
}
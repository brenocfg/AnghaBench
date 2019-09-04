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
#define  FPM_PCTL_ACTION_LAST_CHILD_EXITED 134 
#define  FPM_PCTL_ACTION_SET 133 
#define  FPM_PCTL_ACTION_TIMEOUT 132 
#define  FPM_PCTL_STATE_FINISHING 131 
#define  FPM_PCTL_STATE_NORMAL 130 
#define  FPM_PCTL_STATE_RELOADING 129 
#define  FPM_PCTL_STATE_TERMINATING 128 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  fpm_pctl_action_last () ; 
 int /*<<< orphan*/  fpm_pctl_action_next () ; 
 int /*<<< orphan*/  fpm_signal_sent ; 
 int fpm_state ; 
 int /*<<< orphan*/ * fpm_state_names ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void fpm_pctl(int new_state, int action) /* {{{ */
{
	switch (action) {
		case FPM_PCTL_ACTION_SET :
			if (fpm_state == new_state) { /* already in progress - just ignore duplicate signal */
				return;
			}

			switch (fpm_state) { /* check which states can be overridden */
				case FPM_PCTL_STATE_NORMAL :
					/* 'normal' can be overridden by any other state */
					break;
				case FPM_PCTL_STATE_RELOADING :
					/* 'reloading' can be overridden by 'finishing' */
					if (new_state == FPM_PCTL_STATE_FINISHING) break;
				case FPM_PCTL_STATE_FINISHING :
					/* 'reloading' and 'finishing' can be overridden by 'terminating' */
					if (new_state == FPM_PCTL_STATE_TERMINATING) break;
				case FPM_PCTL_STATE_TERMINATING :
					/* nothing can override 'terminating' state */
					zlog(ZLOG_DEBUG, "not switching to '%s' state, because already in '%s' state",
						fpm_state_names[new_state], fpm_state_names[fpm_state]);
					return;
			}

			fpm_signal_sent = 0;
			fpm_state = new_state;

			zlog(ZLOG_DEBUG, "switching to '%s' state", fpm_state_names[fpm_state]);
			/* fall down */

		case FPM_PCTL_ACTION_TIMEOUT :
			fpm_pctl_action_next();
			break;
		case FPM_PCTL_ACTION_LAST_CHILD_EXITED :
			fpm_pctl_action_last();
			break;

	}
}
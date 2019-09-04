#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int process_control_timeout; } ;
struct TYPE_3__ {int /*<<< orphan*/  running_children; } ;

/* Variables and functions */
 scalar_t__ FPM_PCTL_STATE_TERMINATING ; 
 int SIGKILL ; 
 scalar_t__ SIGQUIT ; 
 int SIGTERM ; 
 TYPE_2__ fpm_global_config ; 
 TYPE_1__ fpm_globals ; 
 int /*<<< orphan*/  fpm_pctl_action_last () ; 
 int /*<<< orphan*/  fpm_pctl_kill_all (int) ; 
 int /*<<< orphan*/  fpm_pctl_timeout_set (int) ; 
 scalar_t__ fpm_signal_sent ; 
 scalar_t__ fpm_state ; 

__attribute__((used)) static void fpm_pctl_action_next() /* {{{ */
{
	int sig, timeout;

	if (!fpm_globals.running_children) {
		fpm_pctl_action_last();
	}

	if (fpm_signal_sent == 0) {
		if (fpm_state == FPM_PCTL_STATE_TERMINATING) {
			sig = SIGTERM;
		} else {
			sig = SIGQUIT;
		}
		timeout = fpm_global_config.process_control_timeout;
	} else {
		if (fpm_signal_sent == SIGQUIT) {
			sig = SIGTERM;
		} else {
			sig = SIGKILL;
		}
		timeout = 1;
	}

	fpm_pctl_kill_all(sig);
	fpm_signal_sent = sig;
	fpm_pctl_timeout_set(timeout);
}
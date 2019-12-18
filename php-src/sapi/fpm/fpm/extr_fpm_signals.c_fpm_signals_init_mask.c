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
 int NSIG ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  block_sigset ; 
 int /*<<< orphan*/ ** fpm_signal_names ; 
 scalar_t__ sigaddset (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 

int fpm_signals_init_mask(int *signum_array, size_t size) /* {{{ */
{
	size_t i = 0;
	if (0 > sigemptyset(&block_sigset)) {
		zlog(ZLOG_SYSERROR, "failed to prepare signal block mask: sigemptyset()");
		return -1;
	}
	for (i = 0; i < size; ++i) {
		int sig_i = signum_array[i];
		if (0 > sigaddset(&block_sigset, sig_i)) {
			if (sig_i <= NSIG && fpm_signal_names[sig_i] != NULL) {
				zlog(ZLOG_SYSERROR, "failed to prepare signal block mask: sigaddset(%s)",
						fpm_signal_names[sig_i]);
			} else {
				zlog(ZLOG_SYSERROR, "failed to prepare signal block mask: sigaddset(%d)", sig_i);
			}
			return -1;
		}
	}
	return 0;
}
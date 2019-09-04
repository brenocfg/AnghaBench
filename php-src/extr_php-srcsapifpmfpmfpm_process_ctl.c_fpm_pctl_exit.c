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
 int /*<<< orphan*/  FPM_CLEANUP_PARENT_EXIT_MAIN ; 
 int /*<<< orphan*/  FPM_EXIT_OK ; 
 int /*<<< orphan*/  ZLOG_NOTICE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_cleanups_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_conf_unlink_pid () ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void fpm_pctl_exit() /* {{{ */
{
	zlog(ZLOG_NOTICE, "exiting, bye-bye!");

	fpm_conf_unlink_pid();
	fpm_cleanups_run(FPM_CLEANUP_PARENT_EXIT_MAIN);
	exit(FPM_EXIT_OK);
}
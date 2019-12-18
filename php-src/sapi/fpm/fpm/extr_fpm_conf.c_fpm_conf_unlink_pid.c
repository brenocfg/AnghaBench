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
struct TYPE_2__ {scalar_t__ pid_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 TYPE_1__ fpm_global_config ; 
 scalar_t__ unlink (scalar_t__) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

int fpm_conf_unlink_pid() /* {{{ */
{
	if (fpm_global_config.pid_file) {
		if (0 > unlink(fpm_global_config.pid_file)) {
			zlog(ZLOG_SYSERROR, "Unable to remove the PID file (%s).", fpm_global_config.pid_file);
			return -1;
		}
	}
	return 0;
}
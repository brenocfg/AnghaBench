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
struct TYPE_4__ {scalar_t__ pid_file; } ;
struct TYPE_3__ {scalar_t__ parent_pid; } ;

/* Variables and functions */
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  close (int) ; 
 int creat (scalar_t__,int) ; 
 TYPE_2__ fpm_global_config ; 
 TYPE_1__ fpm_globals ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 
 int write (int,char*,int) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 

int fpm_conf_write_pid() /* {{{ */
{
	int fd;

	if (fpm_global_config.pid_file) {
		char buf[64];
		int len;

		unlink(fpm_global_config.pid_file);
		fd = creat(fpm_global_config.pid_file, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

		if (fd < 0) {
			zlog(ZLOG_SYSERROR, "Unable to create the PID file (%s).", fpm_global_config.pid_file);
			return -1;
		}

		len = sprintf(buf, "%d", (int) fpm_globals.parent_pid);

		if (len != write(fd, buf, len)) {
			zlog(ZLOG_SYSERROR, "Unable to write to the PID file.");
			close(fd);
			return -1;
		}
		close(fd);
	}
	return 0;
}
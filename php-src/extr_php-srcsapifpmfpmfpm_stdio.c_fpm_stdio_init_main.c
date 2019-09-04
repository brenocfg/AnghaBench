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
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ dup2 (int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

int fpm_stdio_init_main() /* {{{ */
{
	int fd = open("/dev/null", O_RDWR);

	if (0 > fd) {
		zlog(ZLOG_SYSERROR, "failed to init stdio: open(\"/dev/null\")");
		return -1;
	}

	if (0 > dup2(fd, STDIN_FILENO) || 0 > dup2(fd, STDOUT_FILENO)) {
		zlog(ZLOG_SYSERROR, "failed to init stdio: dup2()");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}
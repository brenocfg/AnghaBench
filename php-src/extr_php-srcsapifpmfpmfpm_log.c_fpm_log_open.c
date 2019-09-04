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
struct fpm_worker_pool_s {int log_fd; TYPE_1__* config; struct fpm_worker_pool_s* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  access_log; } ;

/* Variables and functions */
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fpm_pctl_kill_all (int /*<<< orphan*/ ) ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 

int fpm_log_open(int reopen) /* {{{ */
{
	struct fpm_worker_pool_s *wp;
	int ret = 1;

	int fd;
	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		if (!wp->config->access_log) {
			continue;
		}
		ret = 0;

		fd = open(wp->config->access_log, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		if (0 > fd) {
			zlog(ZLOG_SYSERROR, "failed to open access log (%s)", wp->config->access_log);
			return -1;
		} else {
			zlog(ZLOG_DEBUG, "open access log (%s)", wp->config->access_log);
		}

		if (reopen) {
			dup2(fd, wp->log_fd);
			close(fd);
			fd = wp->log_fd;
			fpm_pctl_kill_all(SIGQUIT);
		} else {
			wp->log_fd = fd;
		}

		if (0 > fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC)) {
			zlog(ZLOG_WARNING, "failed to change attribute of access_log");
		}
	}

	return ret;
}
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
struct timeval {int tv_sec; int /*<<< orphan*/  tv_usec; } ;
struct rlimit {void* rlim_cur; void* rlim_max; } ;
struct fpm_worker_pool_s {struct fpm_worker_pool_s* next; } ;
typedef  void* rlim_t ;
typedef  int /*<<< orphan*/  readval ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_4__ {int rlimit_core; int process_priority; scalar_t__ daemonize; scalar_t__ rlimit_files; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent_pid; int /*<<< orphan*/ * send_config_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FPM_CLEANUP_PARENT_EXIT ; 
 int /*<<< orphan*/  FPM_EXIT_OK ; 
 int /*<<< orphan*/  FPM_EXIT_SOFTWARE ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 scalar_t__ RLIM_INFINITY ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  ZLOG_NOTICE ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  fpm_cleanups_run (int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_clock_init () ; 
 TYPE_2__ fpm_global_config ; 
 TYPE_1__ fpm_globals ; 
 int /*<<< orphan*/  fpm_pagesize ; 
 scalar_t__ fpm_unix_conf_wp (struct fpm_worker_pool_s*) ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  getpagesize () ; 
 int /*<<< orphan*/  getpid () ; 
 int pipe (int /*<<< orphan*/ *) ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 

int fpm_unix_init_main() /* {{{ */
{
	struct fpm_worker_pool_s *wp;
	int is_root = !geteuid();

	if (fpm_global_config.rlimit_files) {
		struct rlimit r;

		r.rlim_max = r.rlim_cur = (rlim_t) fpm_global_config.rlimit_files;

		if (0 > setrlimit(RLIMIT_NOFILE, &r)) {
			zlog(ZLOG_SYSERROR, "failed to set rlimit_core for this pool. Please check your system limits or decrease rlimit_files. setrlimit(RLIMIT_NOFILE, %d)", fpm_global_config.rlimit_files);
			return -1;
		}
	}

	if (fpm_global_config.rlimit_core) {
		struct rlimit r;

		r.rlim_max = r.rlim_cur = fpm_global_config.rlimit_core == -1 ? (rlim_t) RLIM_INFINITY : (rlim_t) fpm_global_config.rlimit_core;

		if (0 > setrlimit(RLIMIT_CORE, &r)) {
			zlog(ZLOG_SYSERROR, "failed to set rlimit_core for this pool. Please check your system limits or decrease rlimit_core. setrlimit(RLIMIT_CORE, %d)", fpm_global_config.rlimit_core);
			return -1;
		}
	}

	fpm_pagesize = getpagesize();
	if (fpm_global_config.daemonize) {
		/*
		 * If daemonize, the calling process will die soon
		 * and the master process continues to initialize itself.
		 *
		 * The parent process has then to wait for the master
		 * process to initialize to return a consistent exit
		 * value. For this pupose, the master process will
		 * send \"1\" into the pipe if everything went well
		 * and \"0\" otherwise.
		 */


		struct timeval tv;
		fd_set rfds;
		int ret;

		if (pipe(fpm_globals.send_config_pipe) == -1) {
			zlog(ZLOG_SYSERROR, "failed to create pipe");
			return -1;
		}

		/* then fork */
		pid_t pid = fork();
		switch (pid) {

			case -1 : /* error */
				zlog(ZLOG_SYSERROR, "failed to daemonize");
				return -1;

			case 0 : /* children */
				close(fpm_globals.send_config_pipe[0]); /* close the read side of the pipe */
				break;

			default : /* parent */
				close(fpm_globals.send_config_pipe[1]); /* close the write side of the pipe */

				/*
				 * wait for 10s before exiting with error
				 * the child is supposed to send 1 or 0 into the pipe to tell the parent
				 * how it goes for it
				 */
				FD_ZERO(&rfds);
				FD_SET(fpm_globals.send_config_pipe[0], &rfds);

				tv.tv_sec = 10;
				tv.tv_usec = 0;

				zlog(ZLOG_DEBUG, "The calling process is waiting for the master process to ping via fd=%d", fpm_globals.send_config_pipe[0]);
				ret = select(fpm_globals.send_config_pipe[0] + 1, &rfds, NULL, NULL, &tv);
				if (ret == -1) {
					zlog(ZLOG_SYSERROR, "failed to select");
					exit(FPM_EXIT_SOFTWARE);
				}
				if (ret) { /* data available */
					int readval;
					ret = read(fpm_globals.send_config_pipe[0], &readval, sizeof(readval));
					if (ret == -1) {
						zlog(ZLOG_SYSERROR, "failed to read from pipe");
						exit(FPM_EXIT_SOFTWARE);
					}

					if (ret == 0) {
						zlog(ZLOG_ERROR, "no data have been read from pipe");
						exit(FPM_EXIT_SOFTWARE);
					} else {
						if (readval == 1) {
							zlog(ZLOG_DEBUG, "I received a valid acknowledge from the master process, I can exit without error");
							fpm_cleanups_run(FPM_CLEANUP_PARENT_EXIT);
							exit(FPM_EXIT_OK);
						} else {
							zlog(ZLOG_DEBUG, "The master process returned an error !");
							exit(FPM_EXIT_SOFTWARE);
						}
					}
				} else { /* no date sent ! */
					zlog(ZLOG_ERROR, "the master process didn't send back its status (via the pipe to the calling process)");
				  exit(FPM_EXIT_SOFTWARE);
				}
				exit(FPM_EXIT_SOFTWARE);
		}
	}

	/* continue as a child */
	setsid();
	if (0 > fpm_clock_init()) {
		return -1;
	}

	if (fpm_global_config.process_priority != 64) {
		if (is_root) {
			if (setpriority(PRIO_PROCESS, 0, fpm_global_config.process_priority) < 0) {
				zlog(ZLOG_SYSERROR, "Unable to set priority for the master process");
				return -1;
			}
		} else {
			zlog(ZLOG_NOTICE, "'process.priority' directive is ignored when FPM is not running as root");
		}
	}

	fpm_globals.parent_pid = getpid();
	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		if (0 > fpm_unix_conf_wp(wp)) {
			return -1;
		}
	}

	return 0;
}
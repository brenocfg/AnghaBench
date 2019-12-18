#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char* time_t ;
struct timeval {char* tv_sec; scalar_t__ tv_usec; } ;
struct fpm_worker_pool_s {TYPE_1__* config; int /*<<< orphan*/  scoreboard; } ;
struct fpm_child_s {struct fpm_worker_pool_s* wp; int /*<<< orphan*/  started; int /*<<< orphan*/  scoreboard_i; int /*<<< orphan*/  (* tracer ) (struct fpm_child_s*) ;scalar_t__ idle_kill; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int emergency_restart_threshold; char* emergency_restart_interval; } ;
struct TYPE_5__ {scalar_t__ is_child; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ FPM_EXIT_OK ; 
 int /*<<< orphan*/  FPM_PCTL_ACTION_SET ; 
 int /*<<< orphan*/  FPM_PCTL_STATE_RELOADING ; 
 int SIGBUS ; 
 int SIGQUIT ; 
 int SIGSEGV ; 
 scalar_t__ WCOREDUMP (int) ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int WNOHANG ; 
 int WTERMSIG (int) ; 
 int WUNTRACED ; 
 int ZLOG_ALERT ; 
 int ZLOG_DEBUG ; 
 int ZLOG_NOTICE ; 
 int ZLOG_WARNING ; 
 int fault ; 
 int /*<<< orphan*/  fpm_child_close (struct fpm_child_s*,int) ; 
 struct fpm_child_s* fpm_child_find (int) ; 
 int /*<<< orphan*/  fpm_child_unlink (struct fpm_child_s*) ; 
 int /*<<< orphan*/  fpm_children_make (struct fpm_worker_pool_s*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_clock_get (struct timeval*) ; 
 TYPE_3__ fpm_global_config ; 
 TYPE_2__ fpm_globals ; 
 int /*<<< orphan*/  fpm_pctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_pctl_can_spawn_children () ; 
 int /*<<< orphan*/  fpm_pctl_child_exited () ; 
 int /*<<< orphan*/  fpm_scoreboard_proc_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** fpm_signal_names ; 
 char** last_faults ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  stub1 (struct fpm_child_s*) ; 
 int /*<<< orphan*/  timersub (struct timeval*,int /*<<< orphan*/ *,struct timeval*) ; 
 int waitpid (int,int*,int) ; 
 int /*<<< orphan*/  zlog (int,char*,int,...) ; 

void fpm_children_bury() /* {{{ */
{
	int status;
	pid_t pid;
	struct fpm_child_s *child;

	while ( (pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
		char buf[128];
		int severity = ZLOG_NOTICE;
		int restart_child = 1;

		child = fpm_child_find(pid);

		if (WIFEXITED(status)) {

			snprintf(buf, sizeof(buf), "with code %d", WEXITSTATUS(status));

			/* if it's been killed because of dynamic process management
			 * don't restart it automatically
			 */
			if (child && child->idle_kill) {
				restart_child = 0;
			}

			if (WEXITSTATUS(status) != FPM_EXIT_OK) {
				severity = ZLOG_WARNING;
			}

		} else if (WIFSIGNALED(status)) {
			const char *signame = fpm_signal_names[WTERMSIG(status)];
#ifdef WCOREDUMP
			const char *have_core = WCOREDUMP(status) ? " - core dumped" : "";
#else
			const char* have_core = "";
#endif

			if (signame == NULL) {
				signame = "";
			}

			snprintf(buf, sizeof(buf), "on signal %d (%s%s)", WTERMSIG(status), signame, have_core);

			/* if it's been killed because of dynamic process management
			 * don't restart it automatically
			 */
			if (child && child->idle_kill && WTERMSIG(status) == SIGQUIT) {
				restart_child = 0;
			}

			if (WTERMSIG(status) != SIGQUIT) { /* possible request loss */
				severity = ZLOG_WARNING;
			}
		} else if (WIFSTOPPED(status)) {

			zlog(ZLOG_NOTICE, "child %d stopped for tracing", (int) pid);

			if (child && child->tracer) {
				child->tracer(child);
			}

			continue;
		}

		if (child) {
			struct fpm_worker_pool_s *wp = child->wp;
			struct timeval tv1, tv2;

			fpm_child_unlink(child);

			fpm_scoreboard_proc_free(wp->scoreboard, child->scoreboard_i);

			fpm_clock_get(&tv1);

			timersub(&tv1, &child->started, &tv2);

			if (restart_child) {
				if (!fpm_pctl_can_spawn_children()) {
					severity = ZLOG_DEBUG;
				}
				zlog(severity, "[pool %s] child %d exited %s after %ld.%06d seconds from start", child->wp->config->name, (int) pid, buf, tv2.tv_sec, (int) tv2.tv_usec);
			} else {
				zlog(ZLOG_DEBUG, "[pool %s] child %d has been killed by the process management after %ld.%06d seconds from start", child->wp->config->name, (int) pid, tv2.tv_sec, (int) tv2.tv_usec);
			}

			fpm_child_close(child, 1 /* in event_loop */);

			fpm_pctl_child_exited();

			if (last_faults && (WTERMSIG(status) == SIGSEGV || WTERMSIG(status) == SIGBUS)) {
				time_t now = tv1.tv_sec;
				int restart_condition = 1;
				int i;

				last_faults[fault++] = now;

				if (fault == fpm_global_config.emergency_restart_threshold) {
					fault = 0;
				}

				for (i = 0; i < fpm_global_config.emergency_restart_threshold; i++) {
					if (now - last_faults[i] > fpm_global_config.emergency_restart_interval) {
						restart_condition = 0;
						break;
					}
				}

				if (restart_condition) {

					zlog(ZLOG_WARNING, "failed processes threshold (%d in %d sec) is reached, initiating reload", fpm_global_config.emergency_restart_threshold, fpm_global_config.emergency_restart_interval);

					fpm_pctl(FPM_PCTL_STATE_RELOADING, FPM_PCTL_ACTION_SET);
				}
			}

			if (restart_child) {
				fpm_children_make(wp, 1 /* in event loop */, 1, 0);

				if (fpm_globals.is_child) {
					break;
				}
			}
		} else {
			zlog(ZLOG_ALERT, "oops, unknown child (%d) exited %s. Please open a bug report (https://bugs.php.net).", pid, buf);
		}
	}
}
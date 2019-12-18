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
struct __test_metadata {int passed; char* name; int termsig; int /*<<< orphan*/  step; int /*<<< orphan*/  (* fn ) (struct __test_metadata*) ;int /*<<< orphan*/  timeout; scalar_t__ trigger; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int SIGABRT ; 
 int /*<<< orphan*/  TH_LOG_STREAM ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct __test_metadata*) ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

void __run_test(struct __test_metadata *t)
{
	pid_t child_pid;
	int status;

	t->passed = 1;
	t->trigger = 0;
	printf("[ RUN      ] %s\n", t->name);
	alarm(t->timeout);
	child_pid = fork();
	if (child_pid < 0) {
		printf("ERROR SPAWNING TEST CHILD\n");
		t->passed = 0;
	} else if (child_pid == 0) {
		t->fn(t);
		/* return the step that failed or 0 */
		_exit(t->passed ? 0 : t->step);
	} else {
		/* TODO(wad) add timeout support. */
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status)) {
			t->passed = t->termsig == -1 ? !WEXITSTATUS(status) : 0;
			if (t->termsig != -1) {
				fprintf(TH_LOG_STREAM,
					"%s: Test exited normally "
					"instead of by signal (code: %d)\n",
					t->name,
					WEXITSTATUS(status));
			} else if (!t->passed) {
				fprintf(TH_LOG_STREAM,
					"%s: Test failed at step #%d\n",
					t->name,
					WEXITSTATUS(status));
			}
		} else if (WIFSIGNALED(status)) {
			t->passed = 0;
			if (WTERMSIG(status) == SIGABRT) {
				fprintf(TH_LOG_STREAM,
					"%s: Test terminated by assertion\n",
					t->name);
			} else if (WTERMSIG(status) == t->termsig) {
				t->passed = 1;
			} else {
				fprintf(TH_LOG_STREAM,
					"%s: Test terminated unexpectedly "
					"by signal %d\n",
					t->name,
					WTERMSIG(status));
			}
		} else {
			fprintf(TH_LOG_STREAM,
				"%s: Test ended in some other way [%u]\n",
				t->name,
				status);
		}
	}
	printf("[     %4s ] %s\n", (t->passed ? "OK" : "FAIL"), t->name);
	alarm(0);
}
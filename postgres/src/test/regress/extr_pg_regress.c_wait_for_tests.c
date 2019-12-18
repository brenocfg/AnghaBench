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
typedef  int /*<<< orphan*/  instr_time ;
typedef  scalar_t__ PID_TYPE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetExitCodeProcess (scalar_t__,scalar_t__*) ; 
 char* GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_PID ; 
 int WAIT_OBJECT_0 ; 
 int WaitForMultipleObjects (int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__* pg_malloc (int) ; 
 int /*<<< orphan*/  status (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ wait (int*) ; 

__attribute__((used)) static void
wait_for_tests(PID_TYPE * pids, int *statuses, instr_time *stoptimes,
			   char **names, int num_tests)
{
	int			tests_left;
	int			i;

#ifdef WIN32
	PID_TYPE   *active_pids = pg_malloc(num_tests * sizeof(PID_TYPE));

	memcpy(active_pids, pids, num_tests * sizeof(PID_TYPE));
#endif

	tests_left = num_tests;
	while (tests_left > 0)
	{
		PID_TYPE	p;

#ifndef WIN32
		int			exit_status;

		p = wait(&exit_status);

		if (p == INVALID_PID)
		{
			fprintf(stderr, _("failed to wait for subprocesses: %s\n"),
					strerror(errno));
			exit(2);
		}
#else
		DWORD		exit_status;
		int			r;

		r = WaitForMultipleObjects(tests_left, active_pids, FALSE, INFINITE);
		if (r < WAIT_OBJECT_0 || r >= WAIT_OBJECT_0 + tests_left)
		{
			fprintf(stderr, _("failed to wait for subprocesses: error code %lu\n"),
					GetLastError());
			exit(2);
		}
		p = active_pids[r - WAIT_OBJECT_0];
		/* compact the active_pids array */
		active_pids[r - WAIT_OBJECT_0] = active_pids[tests_left - 1];
#endif							/* WIN32 */

		for (i = 0; i < num_tests; i++)
		{
			if (p == pids[i])
			{
#ifdef WIN32
				GetExitCodeProcess(pids[i], &exit_status);
				CloseHandle(pids[i]);
#endif
				pids[i] = INVALID_PID;
				statuses[i] = (int) exit_status;
				INSTR_TIME_SET_CURRENT(stoptimes[i]);
				if (names)
					status(" %s", names[i]);
				tests_left--;
				break;
			}
		}
	}

#ifdef WIN32
	free(active_pids);
#endif
}
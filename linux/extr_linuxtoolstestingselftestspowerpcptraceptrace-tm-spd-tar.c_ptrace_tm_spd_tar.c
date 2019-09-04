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
typedef  int pid_t ;

/* Variables and functions */
 int IPC_CREAT ; 
 int /*<<< orphan*/  IPC_PRIVATE ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int fork () ; 
 int /*<<< orphan*/  have_htm () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int* pptr ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  shm_id ; 
 scalar_t__ shmat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shmdt (int**) ; 
 int /*<<< orphan*/  shmget (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tm_spd_tar () ; 
 int trace_tm_spd_tar (int) ; 
 int wait (int*) ; 

int ptrace_tm_spd_tar(void)
{
	pid_t pid;
	int ret, status;

	SKIP_IF(!have_htm());
	shm_id = shmget(IPC_PRIVATE, sizeof(int) * 3, 0777|IPC_CREAT);
	pid = fork();
	if (pid == 0)
		tm_spd_tar();

	pptr = (int *)shmat(shm_id, NULL, 0);
	pptr[0] = 0;
	pptr[1] = 0;

	if (pid) {
		while (!pptr[2])
			asm volatile("" : : : "memory");
		ret = trace_tm_spd_tar(pid);
		if (ret) {
			kill(pid, SIGTERM);
			shmdt(&pptr);
			shmctl(shm_id, IPC_RMID, NULL);
			return TEST_FAIL;
		}

		shmdt(&pptr);

		ret = wait(&status);
		shmctl(shm_id, IPC_RMID, NULL);
		if (ret != pid) {
			printf("Child's exit status not captured\n");
			return TEST_FAIL;
		}

		return (WIFEXITED(status) && WEXITSTATUS(status)) ? TEST_FAIL :
			TEST_PASS;
	}
	return TEST_PASS;
}
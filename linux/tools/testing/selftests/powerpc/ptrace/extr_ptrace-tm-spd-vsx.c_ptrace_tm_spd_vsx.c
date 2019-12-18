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
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int fork () ; 
 int* fp_load ; 
 int* fp_load_ckpt ; 
 int* fp_load_ckpt_new ; 
 int* fp_load_new ; 
 int /*<<< orphan*/  have_htm () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int* pptr ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rand () ; 
 int /*<<< orphan*/  shm_id ; 
 scalar_t__ shmat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shmdt (void*) ; 
 int /*<<< orphan*/  shmget (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tm_spd_vsx () ; 
 int trace_tm_spd_vsx (int) ; 
 int wait (int*) ; 

int ptrace_tm_spd_vsx(void)
{
	pid_t pid;
	int ret, status, i;

	SKIP_IF(!have_htm());
	shm_id = shmget(IPC_PRIVATE, sizeof(int) * 3, 0777|IPC_CREAT);

	for (i = 0; i < 128; i++) {
		fp_load[i] = 1 + rand();
		fp_load_new[i] = 1 + 2 * rand();
		fp_load_ckpt[i] = 1 + 3 * rand();
		fp_load_ckpt_new[i] = 1 + 4 * rand();
	}

	pid = fork();
	if (pid < 0) {
		perror("fork() failed");
		return TEST_FAIL;
	}

	if (pid == 0)
		tm_spd_vsx();

	if (pid) {
		pptr = (int *)shmat(shm_id, NULL, 0);
		while (!pptr[2])
			asm volatile("" : : : "memory");

		ret = trace_tm_spd_vsx(pid);
		if (ret) {
			kill(pid, SIGKILL);
			shmdt((void *)pptr);
			shmctl(shm_id, IPC_RMID, NULL);
			return TEST_FAIL;
		}

		shmdt((void *)pptr);
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
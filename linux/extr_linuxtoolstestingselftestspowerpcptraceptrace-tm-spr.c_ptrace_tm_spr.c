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
struct shared {int dummy; } ;
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
 int /*<<< orphan*/  have_htm () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct shared* pptr ; 
 int* pptr1 ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  shm_id ; 
 int /*<<< orphan*/  shm_id1 ; 
 scalar_t__ shmat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shmdt (void*) ; 
 int /*<<< orphan*/  shmget (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tm_spr () ; 
 int trace_tm_spr (int) ; 
 int wait (int*) ; 

int ptrace_tm_spr(void)
{
	pid_t pid;
	int ret, status;

	SKIP_IF(!have_htm());
	shm_id = shmget(IPC_PRIVATE, sizeof(struct shared), 0777|IPC_CREAT);
	shm_id1 = shmget(IPC_PRIVATE, sizeof(int), 0777|IPC_CREAT);
	pid = fork();
	if (pid < 0) {
		perror("fork() failed");
		return TEST_FAIL;
	}

	if (pid == 0)
		tm_spr();

	if (pid) {
		pptr = (struct shared *)shmat(shm_id, NULL, 0);
		pptr1 = (int *)shmat(shm_id1, NULL, 0);

		while (!pptr1[0])
			asm volatile("" : : : "memory");
		ret = trace_tm_spr(pid);
		if (ret) {
			kill(pid, SIGKILL);
			shmdt((void *)pptr);
			shmdt((void *)pptr1);
			shmctl(shm_id, IPC_RMID, NULL);
			shmctl(shm_id1, IPC_RMID, NULL);
			return TEST_FAIL;
		}

		shmdt((void *)pptr);
		shmdt((void *)pptr1);
		ret = wait(&status);
		shmctl(shm_id, IPC_RMID, NULL);
		shmctl(shm_id1, IPC_RMID, NULL);
		if (ret != pid) {
			printf("Child's exit status not captured\n");
			return TEST_FAIL;
		}

		return (WIFEXITED(status) && WEXITSTATUS(status)) ? TEST_FAIL :
			TEST_PASS;
	}
	return TEST_PASS;
}
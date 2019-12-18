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
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  expect_gp (int) ; 
 int /*<<< orphan*/  expect_ok (int) ; 
 int fork () ; 
 scalar_t__ ioperm (int,int,int) ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ setresuid (int,int,int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int main(void)
{
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0)
		err(1, "sched_setaffinity to CPU 0");

	expect_gp(0x80);
	expect_gp(0xed);

	/*
	 * Probe for ioperm support.  Note that clearing ioperm bits
	 * works even as nonroot.
	 */
	printf("[RUN]\tenable 0x80\n");
	if (ioperm(0x80, 1, 1) != 0) {
		printf("[OK]\tioperm(0x80, 1, 1) failed (%d) -- try running as root\n",
		       errno);
		return 0;
	}
	expect_ok(0x80);
	expect_gp(0xed);

	printf("[RUN]\tdisable 0x80\n");
	if (ioperm(0x80, 1, 0) != 0) {
		printf("[FAIL]\tioperm(0x80, 1, 0) failed (%d)", errno);
		return 1;
	}
	expect_gp(0x80);
	expect_gp(0xed);

	/* Make sure that fork() preserves ioperm. */
	if (ioperm(0x80, 1, 1) != 0) {
		printf("[FAIL]\tioperm(0x80, 1, 0) failed (%d)", errno);
		return 1;
	}

	pid_t child = fork();
	if (child == -1)
		err(1, "fork");

	if (child == 0) {
		printf("[RUN]\tchild: check that we inherited permissions\n");
		expect_ok(0x80);
		expect_gp(0xed);
		return 0;
	} else {
		int status;
		if (waitpid(child, &status, 0) != child ||
		    !WIFEXITED(status)) {
			printf("[FAIL]\tChild died\n");
			nerrs++;
		} else if (WEXITSTATUS(status) != 0) {
			printf("[FAIL]\tChild failed\n");
			nerrs++;
		} else {
			printf("[OK]\tChild succeeded\n");
		}
	}

	/* Test the capability checks. */

	printf("\tDrop privileges\n");
	if (setresuid(1, 1, 1) != 0) {
		printf("[WARN]\tDropping privileges failed\n");
		return 0;
	}

	printf("[RUN]\tdisable 0x80\n");
	if (ioperm(0x80, 1, 0) != 0) {
		printf("[FAIL]\tioperm(0x80, 1, 0) failed (%d)", errno);
		return 1;
	}
	printf("[OK]\tit worked\n");

	printf("[RUN]\tenable 0x80 again\n");
	if (ioperm(0x80, 1, 1) == 0) {
		printf("[FAIL]\tit succeeded but should have failed.\n");
		return 1;
	}
	printf("[OK]\tit failed\n");
	return 0;
}
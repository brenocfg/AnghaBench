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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 scalar_t__ TEST_int_eq (int,scalar_t__) ; 
 int /*<<< orphan*/  TEST_int_ge (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  test_drbg_reseed (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unhook_drbg (int /*<<< orphan*/ *) ; 
 int waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_drbg_reseed_after_fork(RAND_DRBG *master,
                                       RAND_DRBG *public,
                                       RAND_DRBG *private)
{
    pid_t pid;
    int status=0;

    pid = fork();
    if (!TEST_int_ge(pid, 0))
        return 0;

    if (pid > 0) {
        /* I'm the parent; wait for the child and check its exit code */
        return TEST_int_eq(waitpid(pid, &status, 0), pid) && TEST_int_eq(status, 0);
    }

    /* I'm the child; check whether all three DRBGs reseed. */
    if (!TEST_true(test_drbg_reseed(1, master, public, private, 1, 1, 1, 0)))
        status = 1;

    /* Remove hooks  */
    unhook_drbg(master);
    unhook_drbg(public);
    unhook_drbg(private);
    exit(status);
}
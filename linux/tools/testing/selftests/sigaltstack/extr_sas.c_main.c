#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_mask; } ;
struct TYPE_9__ {int ss_flags; void* ss_size; scalar_t__ ss_sp; } ;
typedef  TYPE_2__ stack_t ;
struct TYPE_8__ {void* ss_size; scalar_t__ ss_sp; } ;
struct TYPE_10__ {TYPE_1__ uc_stack; int /*<<< orphan*/ * uc_link; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int EXIT_FAILURE ; 
 int MAP_ANONYMOUS ; 
 scalar_t__ MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int MAP_STACK ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int SA_ONSTACK ; 
 int SA_SIGINFO ; 
 void* SIGSTKSZ ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int SS_AUTODISARM ; 
 int SS_DISABLE ; 
 int SS_ONSTACK ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  getcontext (TYPE_3__*) ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int) ; 
 int /*<<< orphan*/  ksft_exit_pass () ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  ksft_set_plan (int) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*) ; 
 int /*<<< orphan*/  makecontext (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,void*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_usr1 ; 
 int /*<<< orphan*/  my_usr2 ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int sigaltstack (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sstack ; 
 int strerror (scalar_t__) ; 
 int /*<<< orphan*/  switch_fn ; 
 TYPE_3__ uc ; 
 scalar_t__ ustack ; 

int main(void)
{
	struct sigaction act;
	stack_t stk;
	int err;

	ksft_print_header();
	ksft_set_plan(3);

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_ONSTACK | SA_SIGINFO;
	act.sa_sigaction = my_usr1;
	sigaction(SIGUSR1, &act, NULL);
	act.sa_sigaction = my_usr2;
	sigaction(SIGUSR2, &act, NULL);
	sstack = mmap(NULL, SIGSTKSZ, PROT_READ | PROT_WRITE,
		      MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	if (sstack == MAP_FAILED) {
		ksft_exit_fail_msg("mmap() - %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	err = sigaltstack(NULL, &stk);
	if (err) {
		ksft_exit_fail_msg("sigaltstack() - %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (stk.ss_flags == SS_DISABLE) {
		ksft_test_result_pass(
				"Initial sigaltstack state was SS_DISABLE\n");
	} else {
		ksft_exit_fail_msg("Initial sigaltstack state was %x; "
		       "should have been SS_DISABLE\n", stk.ss_flags);
		return EXIT_FAILURE;
	}

	stk.ss_sp = sstack;
	stk.ss_size = SIGSTKSZ;
	stk.ss_flags = SS_ONSTACK | SS_AUTODISARM;
	err = sigaltstack(&stk, NULL);
	if (err) {
		if (errno == EINVAL) {
			ksft_exit_skip(
				"[NOTE]\tThe running kernel doesn't support SS_AUTODISARM\n");
			/*
			 * If test cases for the !SS_AUTODISARM variant were
			 * added, we could still run them.  We don't have any
			 * test cases like that yet, so just exit and report
			 * success.
			 */
			return 0;
		} else {
			ksft_exit_fail_msg(
				"sigaltstack(SS_ONSTACK | SS_AUTODISARM)  %s\n",
					strerror(errno));
			return EXIT_FAILURE;
		}
	}

	ustack = mmap(NULL, SIGSTKSZ, PROT_READ | PROT_WRITE,
		      MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	if (ustack == MAP_FAILED) {
		ksft_exit_fail_msg("mmap() - %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	getcontext(&uc);
	uc.uc_link = NULL;
	uc.uc_stack.ss_sp = ustack;
	uc.uc_stack.ss_size = SIGSTKSZ;
	makecontext(&uc, switch_fn, 0);
	raise(SIGUSR1);

	err = sigaltstack(NULL, &stk);
	if (err) {
		ksft_exit_fail_msg("sigaltstack() - %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (stk.ss_flags != SS_AUTODISARM) {
		ksft_exit_fail_msg("ss_flags=%x, should be SS_AUTODISARM\n",
				stk.ss_flags);
		exit(EXIT_FAILURE);
	}
	ksft_test_result_pass(
			"sigaltstack is still SS_AUTODISARM after signal\n");

	ksft_exit_pass();
	return 0;
}
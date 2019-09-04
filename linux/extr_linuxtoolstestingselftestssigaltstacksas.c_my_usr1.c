#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stk_data {int flag; int /*<<< orphan*/  msg; } ;
struct TYPE_3__ {scalar_t__ ss_flags; } ;
typedef  TYPE_1__ stack_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 unsigned long SIGSTKSZ ; 
 scalar_t__ SS_DISABLE ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,...) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int /*<<< orphan*/  ksft_print_msg (char*,...) ; 
 int /*<<< orphan*/  ksft_test_result_fail (char*,scalar_t__) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*) ; 
 int /*<<< orphan*/  msg ; 
 int /*<<< orphan*/  sc ; 
 int sigaltstack (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ sstack ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swapcontext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uc ; 

void my_usr1(int sig, siginfo_t *si, void *u)
{
	char *aa;
	int err;
	stack_t stk;
	struct stk_data *p;

#if __s390x__
	register unsigned long sp asm("%15");
#else
	register unsigned long sp asm("sp");
#endif

	if (sp < (unsigned long)sstack ||
			sp >= (unsigned long)sstack + SIGSTKSZ) {
		ksft_exit_fail_msg("SP is not on sigaltstack\n");
	}
	/* put some data on stack. other sighandler will try to overwrite it */
	aa = alloca(1024);
	assert(aa);
	p = (struct stk_data *)(aa + 512);
	strcpy(p->msg, msg);
	p->flag = 1;
	ksft_print_msg("[RUN]\tsignal USR1\n");
	err = sigaltstack(NULL, &stk);
	if (err) {
		ksft_exit_fail_msg("sigaltstack() - %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (stk.ss_flags != SS_DISABLE)
		ksft_test_result_fail("tss_flags=%x, should be SS_DISABLE\n",
				stk.ss_flags);
	else
		ksft_test_result_pass(
				"sigaltstack is disabled in sighandler\n");
	swapcontext(&sc, &uc);
	ksft_print_msg("%s\n", p->msg);
	if (!p->flag) {
		ksft_exit_skip("[RUN]\tAborting\n");
		exit(EXIT_FAILURE);
	}
}
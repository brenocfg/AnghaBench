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
struct stk_data {scalar_t__ flag; int /*<<< orphan*/  msg; } ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 char* alloca (int) ; 
 int /*<<< orphan*/  ksft_print_msg (char*) ; 
 int /*<<< orphan*/  ksft_test_result_fail (char*) ; 
 struct stk_data* memmem (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg ; 
 int /*<<< orphan*/  msg2 ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void my_usr2(int sig, siginfo_t *si, void *u)
{
	char *aa;
	struct stk_data *p;

	ksft_print_msg("[RUN]\tsignal USR2\n");
	aa = alloca(1024);
	/* dont run valgrind on this */
	/* try to find the data stored by previous sighandler */
	p = memmem(aa, 1024, msg, strlen(msg));
	if (p) {
		ksft_test_result_fail("sigaltstack re-used\n");
		/* corrupt the data */
		strcpy(p->msg, msg2);
		/* tell other sighandler that his data is corrupted */
		p->flag = 0;
	}
}
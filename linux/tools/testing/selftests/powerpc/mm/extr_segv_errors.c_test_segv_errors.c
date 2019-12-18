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
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_sigaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int MAP_ANONYMOUS ; 
 char* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 scalar_t__ SEGV_ACCERR ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int faulted ; 
 int /*<<< orphan*/  getpagesize () ; 
 int /*<<< orphan*/  mb () ; 
 char* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  segv_handler ; 
 scalar_t__ si_code ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 

int test_segv_errors(void)
{
	struct sigaction act = {
		.sa_sigaction = segv_handler,
		.sa_flags = SA_SIGINFO,
	};
	char c, *p = NULL;

	p = mmap(NULL, getpagesize(), 0, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	FAIL_IF(p == MAP_FAILED);

	FAIL_IF(sigaction(SIGSEGV, &act, NULL) != 0);

	faulted = false;
	si_code = 0;

	/*
	 * We just need a compiler barrier, but mb() works and has the nice
	 * property of being easy to spot in the disassembly.
	 */
	mb();
	c = *p;
	mb();

	FAIL_IF(!faulted);
	FAIL_IF(si_code != SEGV_ACCERR);

	faulted = false;
	si_code = 0;

	mb();
	*p = c;
	mb();

	FAIL_IF(!faulted);
	FAIL_IF(si_code != SEGV_ACCERR);

	return 0;
}
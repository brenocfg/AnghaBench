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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_TRACEME ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int* var ; 

__attribute__((used)) static void child(int size, int wr)
{
	volatile uint8_t *addr = &var[32 + wr];

	if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) != 0) {
		ksft_print_msg(
			"ptrace(PTRACE_TRACEME) failed: %s\n",
			strerror(errno));
		_exit(1);
	}

	if (raise(SIGSTOP) != 0) {
		ksft_print_msg(
			"raise(SIGSTOP) failed: %s\n", strerror(errno));
		_exit(1);
	}

	if ((uintptr_t) addr % size) {
		ksft_print_msg(
			 "Wrong address write for the given size: %s\n",
			 strerror(errno));
		_exit(1);
	}

	switch (size) {
	case 1:
		*addr = 47;
		break;
	case 2:
		*(uint16_t *)addr = 47;
		break;
	case 4:
		*(uint32_t *)addr = 47;
		break;
	case 8:
		*(uint64_t *)addr = 47;
		break;
	case 16:
		__asm__ volatile ("stp x29, x30, %0" : "=m" (addr[0]));
		break;
	case 32:
		__asm__ volatile ("stp q29, q30, %0" : "=m" (addr[0]));
		break;
	}

	_exit(0);
}
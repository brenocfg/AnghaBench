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

/* Variables and functions */
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  clearhandler (int /*<<< orphan*/ ) ; 
 int nerrs ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sethandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigusr2 ; 

__attribute__((used)) static int test_nonstrict_ss(void)
{
	clearhandler(SIGUSR1);
	clearhandler(SIGTRAP);
	clearhandler(SIGSEGV);
	clearhandler(SIGILL);
	sethandler(SIGUSR2, sigusr2, 0);

	nerrs = 0;

	printf("[RUN]\tClear UC_STRICT_RESTORE_SS and corrupt SS\n");
	raise(SIGUSR2);
	if (!nerrs)
		printf("[OK]\tIt worked\n");

	return nerrs;
}
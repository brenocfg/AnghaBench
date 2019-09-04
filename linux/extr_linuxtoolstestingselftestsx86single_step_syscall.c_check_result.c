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
 unsigned long X86_EFLAGS_TF ; 
 int /*<<< orphan*/  exit (int) ; 
 unsigned long get_eflags () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_eflags (unsigned long) ; 
 scalar_t__ sig_traps ; 

__attribute__((used)) static void check_result(void)
{
	unsigned long new_eflags = get_eflags();
	set_eflags(new_eflags & ~X86_EFLAGS_TF);

	if (!sig_traps) {
		printf("[FAIL]\tNo SIGTRAP\n");
		exit(1);
	}

	if (!(new_eflags & X86_EFLAGS_TF)) {
		printf("[FAIL]\tTF was cleared\n");
		exit(1);
	}

	printf("[OK]\tSurvived with TF set and %d traps\n", (int)sig_traps);
	sig_traps = 0;
}
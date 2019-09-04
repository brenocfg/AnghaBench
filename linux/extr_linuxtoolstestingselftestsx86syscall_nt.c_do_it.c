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
 int /*<<< orphan*/  SYS_getpid ; 
 unsigned long get_eflags () ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_eflags (unsigned long) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_it(unsigned long extraflags)
{
	unsigned long flags;

	set_eflags(get_eflags() | extraflags);
	syscall(SYS_getpid);
	flags = get_eflags();
	if ((flags & extraflags) == extraflags) {
		printf("[OK]\tThe syscall worked and flags are still set\n");
	} else {
		printf("[FAIL]\tThe syscall worked but flags were cleared (flags = 0x%lx but expected 0x%lx set)\n",
		       flags, extraflags);
		nerrs++;
	}
}
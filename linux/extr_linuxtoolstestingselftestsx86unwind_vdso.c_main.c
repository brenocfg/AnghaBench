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
struct TYPE_3__ {char* dli_fname; int /*<<< orphan*/  dli_fbase; } ;
typedef  TYPE_1__ Dl_info ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYSINFO ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SYS_getpid ; 
 int X86_EFLAGS_TF ; 
 int /*<<< orphan*/  dladdr (void*,TYPE_1__*) ; 
 int get_eflags () ; 
 scalar_t__ getauxval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  got_sysinfo ; 
 scalar_t__ nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_eflags (int) ; 
 int /*<<< orphan*/  sethandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigtrap ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,...) ; 
 scalar_t__ sysinfo ; 

int main()
{
	sysinfo = getauxval(AT_SYSINFO);
	printf("\tAT_SYSINFO is 0x%lx\n", sysinfo);

	Dl_info info;
	if (!dladdr((void *)sysinfo, &info)) {
		printf("[WARN]\tdladdr failed on AT_SYSINFO\n");
	} else {
		printf("[OK]\tAT_SYSINFO maps to %s, loaded at 0x%p\n",
		       info.dli_fname, info.dli_fbase);
	}

	sethandler(SIGTRAP, sigtrap, 0);

	syscall(SYS_getpid);  /* Force symbol binding without TF set. */
	printf("[RUN]\tSet TF and check a fast syscall\n");
	set_eflags(get_eflags() | X86_EFLAGS_TF);
	syscall(SYS_getpid, 1, 2, 3, 4, 5, 6);
	if (!got_sysinfo) {
		set_eflags(get_eflags() & ~X86_EFLAGS_TF);

		/*
		 * The most likely cause of this is that you're on Debian or
		 * a Debian-based distro, you're missing libc6-i686, and you're
		 * affected by libc/19006 (https://sourceware.org/PR19006).
		 */
		printf("[WARN]\tsyscall(2) didn't enter AT_SYSINFO\n");
	}

	if (get_eflags() & X86_EFLAGS_TF) {
		printf("[FAIL]\tTF is still set\n");
		nerrs++;
	}

	if (nerrs) {
		printf("[FAIL]\tThere were errors\n");
		return 1;
	} else {
		printf("[OK]\tAll is well\n");
		return 0;
	}
}
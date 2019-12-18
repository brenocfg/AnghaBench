#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* gregs; } ;
struct TYPE_4__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 size_t REG_IP ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 
 int sigtrap_consecutive_syscalls ; 

__attribute__((used)) static void sigtrap(int sig, siginfo_t *info, void *ctx_void)
{
	/*
	 * KVM has some bugs that can cause us to stop making progress.
	 * detect them and complain, but don't infinite loop or fail the
	 * test.
	 */

	ucontext_t *ctx = (ucontext_t*)ctx_void;
	unsigned short *ip = (unsigned short *)ctx->uc_mcontext.gregs[REG_IP];

	if (*ip == 0x340f || *ip == 0x050f) {
		/* The trap was on SYSCALL or SYSENTER */
		sigtrap_consecutive_syscalls++;
		if (sigtrap_consecutive_syscalls > 3) {
			printf("[WARN]\tGot stuck single-stepping -- you probably have a KVM bug\n");
			siglongjmp(jmpbuf, 1);
		}
	} else {
		sigtrap_consecutive_syscalls = 0;
	}
}
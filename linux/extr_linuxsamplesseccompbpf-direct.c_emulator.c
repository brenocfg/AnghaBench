#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* gregs; } ;
struct TYPE_6__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
typedef  int ssize_t ;
struct TYPE_7__ {scalar_t__ si_code; } ;
typedef  TYPE_3__ siginfo_t ;

/* Variables and functions */
 size_t REG_ARG0 ; 
 size_t REG_ARG1 ; 
 size_t REG_ARG2 ; 
 size_t REG_RESULT ; 
 size_t REG_SYSCALL ; 
 int STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ SYS_SECCOMP ; 
 int __NR_write ; 
 int write (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static void emulator(int nr, siginfo_t *info, void *void_context)
{
	ucontext_t *ctx = (ucontext_t *)(void_context);
	int syscall;
	char *buf;
	ssize_t bytes;
	size_t len;
	if (info->si_code != SYS_SECCOMP)
		return;
	if (!ctx)
		return;
	syscall = ctx->uc_mcontext.gregs[REG_SYSCALL];
	buf = (char *) ctx->uc_mcontext.gregs[REG_ARG1];
	len = (size_t) ctx->uc_mcontext.gregs[REG_ARG2];

	if (syscall != __NR_write)
		return;
	if (ctx->uc_mcontext.gregs[REG_ARG0] != STDERR_FILENO)
		return;
	/* Redirect stderr messages to stdout. Doesn't handle EINTR, etc */
	ctx->uc_mcontext.gregs[REG_RESULT] = -1;
	if (write(STDOUT_FILENO, "[ERR] ", 6) > 0) {
		bytes = write(STDOUT_FILENO, buf, len);
		ctx->uc_mcontext.gregs[REG_RESULT] = bytes;
	}
	return;
}
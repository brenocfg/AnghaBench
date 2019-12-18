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
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SECCOMP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KSTK_EIP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,long,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_task (struct audit_buffer*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  in_compat_syscall () ; 
 int /*<<< orphan*/  syscall_get_arch (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void audit_seccomp(unsigned long syscall, long signr, int code)
{
	struct audit_buffer *ab;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_SECCOMP);
	if (unlikely(!ab))
		return;
	audit_log_task(ab);
	audit_log_format(ab, " sig=%ld arch=%x syscall=%ld compat=%d ip=0x%lx code=0x%x",
			 signr, syscall_get_arch(current), syscall,
			 in_compat_syscall(), KSTK_EIP(current), code);
	audit_log_end(ab);
}
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
struct kvm_regs {scalar_t__ rax; scalar_t__ rbx; scalar_t__ rcx; scalar_t__ rdx; scalar_t__ rsi; scalar_t__ rdi; scalar_t__ rsp; scalar_t__ rbp; scalar_t__ r8; scalar_t__ r9; scalar_t__ r10; scalar_t__ r11; scalar_t__ r12; scalar_t__ r13; scalar_t__ r14; scalar_t__ r15; scalar_t__ rip; scalar_t__ rflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void compare_regs(struct kvm_regs *left, struct kvm_regs *right)
{
#define REG_COMPARE(reg) \
	TEST_ASSERT(left->reg == right->reg, \
		    "Register " #reg \
		    " values did not match: 0x%llx, 0x%llx\n", \
		    left->reg, right->reg)
	REG_COMPARE(rax);
	REG_COMPARE(rbx);
	REG_COMPARE(rcx);
	REG_COMPARE(rdx);
	REG_COMPARE(rsi);
	REG_COMPARE(rdi);
	REG_COMPARE(rsp);
	REG_COMPARE(rbp);
	REG_COMPARE(r8);
	REG_COMPARE(r9);
	REG_COMPARE(r10);
	REG_COMPARE(r11);
	REG_COMPARE(r12);
	REG_COMPARE(r13);
	REG_COMPARE(r14);
	REG_COMPARE(r15);
	REG_COMPARE(rip);
	REG_COMPARE(rflags);
#undef REG_COMPARE
}
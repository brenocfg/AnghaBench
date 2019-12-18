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
typedef  char* uint8_t ;
struct kvm_regs {int /*<<< orphan*/  rflags; int /*<<< orphan*/  rip; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

void regs_dump(FILE *stream, struct kvm_regs *regs,
	       uint8_t indent)
{
	fprintf(stream, "%*srax: 0x%.16llx rbx: 0x%.16llx "
		"rcx: 0x%.16llx rdx: 0x%.16llx\n",
		indent, "",
		regs->rax, regs->rbx, regs->rcx, regs->rdx);
	fprintf(stream, "%*srsi: 0x%.16llx rdi: 0x%.16llx "
		"rsp: 0x%.16llx rbp: 0x%.16llx\n",
		indent, "",
		regs->rsi, regs->rdi, regs->rsp, regs->rbp);
	fprintf(stream, "%*sr8:  0x%.16llx r9:  0x%.16llx "
		"r10: 0x%.16llx r11: 0x%.16llx\n",
		indent, "",
		regs->r8, regs->r9, regs->r10, regs->r11);
	fprintf(stream, "%*sr12: 0x%.16llx r13: 0x%.16llx "
		"r14: 0x%.16llx r15: 0x%.16llx\n",
		indent, "",
		regs->r12, regs->r13, regs->r14, regs->r15);
	fprintf(stream, "%*srip: 0x%.16llx rfl: 0x%.16llx\n",
		indent, "",
		regs->rip, regs->rflags);
}
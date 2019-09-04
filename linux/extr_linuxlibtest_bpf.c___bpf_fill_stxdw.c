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
struct TYPE_3__ {unsigned int len; struct bpf_insn* insns; } ;
struct TYPE_4__ {TYPE_1__ ptr; } ;
struct bpf_test {int stack_depth; TYPE_2__ u; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 struct bpf_insn BPF_ALU32_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_EXIT_INSN () ; 
 struct bpf_insn BPF_LDX_MEM (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int BPF_MAXINSNS ; 
 int /*<<< orphan*/  BPF_MOV ; 
 struct bpf_insn BPF_STX_XADD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_ST_MEM (int,int /*<<< orphan*/ ,int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R10 ; 
 struct bpf_insn* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __bpf_fill_stxdw(struct bpf_test *self, int size)
{
	unsigned int len = BPF_MAXINSNS;
	struct bpf_insn *insn;
	int i;

	insn = kmalloc_array(len, sizeof(*insn), GFP_KERNEL);
	if (!insn)
		return -ENOMEM;

	insn[0] = BPF_ALU32_IMM(BPF_MOV, R0, 1);
	insn[1] = BPF_ST_MEM(size, R10, -40, 42);

	for (i = 2; i < len - 2; i++)
		insn[i] = BPF_STX_XADD(size, R10, R0, -40);

	insn[len - 2] = BPF_LDX_MEM(size, R0, R10, -40);
	insn[len - 1] = BPF_EXIT_INSN();

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;
	self->stack_depth = 40;

	return 0;
}
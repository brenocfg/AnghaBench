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
struct bpf_test {TYPE_2__ u; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 struct bpf_insn BPF_ALU32_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_EXIT_INSN () ; 
 int /*<<< orphan*/  BPF_JA ; 
 struct bpf_insn BPF_JMP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int BPF_MAXINSNS ; 
 int /*<<< orphan*/  BPF_MOV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  R0 ; 
 struct bpf_insn* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_fill_maxinsns9(struct bpf_test *self)
{
	unsigned int len = BPF_MAXINSNS;
	struct bpf_insn *insn;
	int i;

	insn = kmalloc_array(len, sizeof(*insn), GFP_KERNEL);
	if (!insn)
		return -ENOMEM;

	insn[0] = BPF_JMP_IMM(BPF_JA, 0, 0, len - 2);
	insn[1] = BPF_ALU32_IMM(BPF_MOV, R0, 0xcbababab);
	insn[2] = BPF_EXIT_INSN();

	for (i = 3; i < len - 2; i++)
		insn[i] = BPF_ALU32_IMM(BPF_MOV, R0, 0xfefefefe);

	insn[len - 2] = BPF_EXIT_INSN();
	insn[len - 1] = BPF_JMP_IMM(BPF_JA, 0, 0, -(len - 1));

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	return 0;
}
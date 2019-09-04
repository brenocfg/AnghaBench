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

__attribute__((used)) static int bpf_fill_maxinsns10(struct bpf_test *self)
{
	unsigned int len = BPF_MAXINSNS, hlen = len - 2;
	struct bpf_insn *insn;
	int i;

	insn = kmalloc_array(len, sizeof(*insn), GFP_KERNEL);
	if (!insn)
		return -ENOMEM;

	for (i = 0; i < hlen / 2; i++)
		insn[i] = BPF_JMP_IMM(BPF_JA, 0, 0, hlen - 2 - 2 * i);
	for (i = hlen - 1; i > hlen / 2; i--)
		insn[i] = BPF_JMP_IMM(BPF_JA, 0, 0, hlen - 1 - 2 * i);

	insn[hlen / 2] = BPF_JMP_IMM(BPF_JA, 0, 0, hlen / 2 - 1);
	insn[hlen]     = BPF_ALU32_IMM(BPF_MOV, R0, 0xabababac);
	insn[hlen + 1] = BPF_EXIT_INSN();

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	return 0;
}
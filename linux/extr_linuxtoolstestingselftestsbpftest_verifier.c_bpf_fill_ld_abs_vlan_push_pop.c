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
struct bpf_test {struct bpf_insn* insns; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 struct bpf_insn BPF_ALU32_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BPF_B ; 
 int BPF_CALL ; 
 struct bpf_insn BPF_EXIT_INSN () ; 
 int /*<<< orphan*/  BPF_FUNC_skb_vlan_pop ; 
 int /*<<< orphan*/  BPF_FUNC_skb_vlan_push ; 
 int BPF_JMP ; 
 struct bpf_insn BPF_JMP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  BPF_JNE ; 
 struct bpf_insn BPF_LD_ABS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int BPF_MAXINSNS ; 
 int /*<<< orphan*/  BPF_MOV ; 
 struct bpf_insn BPF_MOV64_IMM (int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_MOV64_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_insn BPF_RAW_INSN (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_REG_1 ; 
 int /*<<< orphan*/  BPF_REG_2 ; 
 int /*<<< orphan*/  BPF_REG_3 ; 
 int /*<<< orphan*/  BPF_REG_6 ; 

__attribute__((used)) static void bpf_fill_ld_abs_vlan_push_pop(struct bpf_test *self)
{
	/* test: {skb->data[0], vlan_push} x 68 + {skb->data[0], vlan_pop} x 68 */
#define PUSH_CNT 51
	unsigned int len = BPF_MAXINSNS;
	struct bpf_insn *insn = self->insns;
	int i = 0, j, k = 0;

	insn[i++] = BPF_MOV64_REG(BPF_REG_6, BPF_REG_1);
loop:
	for (j = 0; j < PUSH_CNT; j++) {
		insn[i++] = BPF_LD_ABS(BPF_B, 0);
		insn[i] = BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0x34, len - i - 2);
		i++;
		insn[i++] = BPF_MOV64_REG(BPF_REG_1, BPF_REG_6);
		insn[i++] = BPF_MOV64_IMM(BPF_REG_2, 1);
		insn[i++] = BPF_MOV64_IMM(BPF_REG_3, 2);
		insn[i++] = BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
					 BPF_FUNC_skb_vlan_push),
		insn[i] = BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, len - i - 2);
		i++;
	}

	for (j = 0; j < PUSH_CNT; j++) {
		insn[i++] = BPF_LD_ABS(BPF_B, 0);
		insn[i] = BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0x34, len - i - 2);
		i++;
		insn[i++] = BPF_MOV64_REG(BPF_REG_1, BPF_REG_6);
		insn[i++] = BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
					 BPF_FUNC_skb_vlan_pop),
		insn[i] = BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, len - i - 2);
		i++;
	}
	if (++k < 5)
		goto loop;

	for (; i < len - 1; i++)
		insn[i] = BPF_ALU32_IMM(BPF_MOV, BPF_REG_0, 0xbef);
	insn[len - 1] = BPF_EXIT_INSN();
}
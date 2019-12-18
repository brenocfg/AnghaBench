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
struct bpf_insn_pos {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ADD ; 
 int /*<<< orphan*/  BPF_ALU64_IMM (int /*<<< orphan*/ ,int,long) ; 
 int /*<<< orphan*/  BPF_EMIT_CALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_FUNC_probe_read ; 
 int /*<<< orphan*/  BPF_JMP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_JNE ; 
 int /*<<< orphan*/  BPF_MOV ; 
 int /*<<< orphan*/  BPF_MOV64_REG (int,int) ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int BPF_REG_ARG1 ; 
 int BPF_REG_ARG2 ; 
 int BPF_REG_ARG3 ; 
 long BPF_REG_SIZE ; 
 int /*<<< orphan*/  JMP_TO_ERROR_CODE ; 
 int check_pos (struct bpf_insn_pos*) ; 
 int /*<<< orphan*/  ins (int /*<<< orphan*/ ,struct bpf_insn_pos*) ; 

__attribute__((used)) static int
gen_read_mem(struct bpf_insn_pos *pos,
	     int src_base_addr_reg,
	     int dst_addr_reg,
	     long offset)
{
	/* mov arg3, src_base_addr_reg */
	if (src_base_addr_reg != BPF_REG_ARG3)
		ins(BPF_MOV64_REG(BPF_REG_ARG3, src_base_addr_reg), pos);
	/* add arg3, #offset */
	if (offset)
		ins(BPF_ALU64_IMM(BPF_ADD, BPF_REG_ARG3, offset), pos);

	/* mov arg2, #reg_size */
	ins(BPF_ALU64_IMM(BPF_MOV, BPF_REG_ARG2, BPF_REG_SIZE), pos);

	/* mov arg1, dst_addr_reg */
	if (dst_addr_reg != BPF_REG_ARG1)
		ins(BPF_MOV64_REG(BPF_REG_ARG1, dst_addr_reg), pos);

	/* Call probe_read  */
	ins(BPF_EMIT_CALL(BPF_FUNC_probe_read), pos);
	/*
	 * Error processing: if read fail, goto error code,
	 * will be relocated. Target should be the start of
	 * error processing code.
	 */
	ins(BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, JMP_TO_ERROR_CODE),
	    pos);

	return check_pos(pos);
}
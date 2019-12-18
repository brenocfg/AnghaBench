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
struct bpf_insn {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct bpf_insn*) ; 
 int BPF_CALL ; 
 struct bpf_insn BPF_EXIT_INSN () ; 
 int /*<<< orphan*/  BPF_FUNC_tail_call ; 
 int BPF_JMP ; 
 struct bpf_insn BPF_LD_MAP_FD (int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_MOV64_IMM (int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_RAW_INSN (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_REG_2 ; 
 int /*<<< orphan*/  BPF_REG_3 ; 
 int bpf_load_program (int,struct bpf_insn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_prog_dummy2(enum bpf_prog_type prog_type, int mfd, int idx)
{
	struct bpf_insn prog[] = {
		BPF_MOV64_IMM(BPF_REG_3, idx),
		BPF_LD_MAP_FD(BPF_REG_2, mfd),
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
			     BPF_FUNC_tail_call),
		BPF_MOV64_IMM(BPF_REG_0, 41),
		BPF_EXIT_INSN(),
	};

	return bpf_load_program(prog_type, prog,
				ARRAY_SIZE(prog), "GPL", 0, NULL, 0);
}
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
 struct bpf_insn BPF_EXIT_INSN () ; 
 struct bpf_insn BPF_MOV64_IMM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int bpf_load_program (int,struct bpf_insn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_prog_dummy1(enum bpf_prog_type prog_type)
{
	struct bpf_insn prog[] = {
		BPF_MOV64_IMM(BPF_REG_0, 42),
		BPF_EXIT_INSN(),
	};

	return bpf_load_program(prog_type, prog,
				ARRAY_SIZE(prog), "GPL", 0, NULL, 0);
}
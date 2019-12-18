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
struct bpf_insn {int /*<<< orphan*/  dst_reg; int /*<<< orphan*/  imm; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  (* bpf_insn_print_t ) (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 scalar_t__ BPF_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_TO_BE ; 

__attribute__((used)) static void print_bpf_end_insn(bpf_insn_print_t verbose,
			       void *private_data,
			       const struct bpf_insn *insn)
{
	verbose(private_data, "(%02x) r%d = %s%d r%d\n",
		insn->code, insn->dst_reg,
		BPF_SRC(insn->code) == BPF_TO_BE ? "be" : "le",
		insn->imm, insn->dst_reg);
}
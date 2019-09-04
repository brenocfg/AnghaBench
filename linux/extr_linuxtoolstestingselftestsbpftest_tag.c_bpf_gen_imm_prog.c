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

/* Variables and functions */
 int /*<<< orphan*/  BPF_ALU64_IMM (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_EXIT_INSN () ; 
 int /*<<< orphan*/  BPF_MOV ; 
 int BPF_REG_10 ; 
 int /*<<< orphan*/ * prog ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bpf_gen_imm_prog(unsigned int insns, int fd_map)
{
	int i;

	srand(time(NULL));
	for (i = 0; i < insns; i++)
		prog[i] = BPF_ALU64_IMM(BPF_MOV, i % BPF_REG_10, rand());
	prog[i - 1] = BPF_EXIT_INSN();
}
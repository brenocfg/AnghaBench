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
typedef  scalar_t__ u8 ;
struct bpf_insn {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 scalar_t__ BPF_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_JMP ; 
 scalar_t__ BPF_JMP32 ; 
 scalar_t__ BPF_ST ; 
 scalar_t__ BPF_STX ; 

__attribute__((used)) static bool insn_no_def(struct bpf_insn *insn)
{
	u8 class = BPF_CLASS(insn->code);

	return (class == BPF_JMP || class == BPF_JMP32 ||
		class == BPF_STX || class == BPF_ST);
}
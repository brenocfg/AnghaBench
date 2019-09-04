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
typedef  scalar_t__ u32 ;
struct bpf_insn {scalar_t__ imm; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ S32_MAX ; 
 scalar_t__ S32_MIN ; 

__attribute__((used)) static int bpf_adj_delta_to_imm(struct bpf_insn *insn, u32 pos, u32 delta,
				u32 curr, const bool probe_pass)
{
	const s64 imm_min = S32_MIN, imm_max = S32_MAX;
	s64 imm = insn->imm;

	if (curr < pos && curr + imm + 1 > pos)
		imm += delta;
	else if (curr > pos + delta && curr + imm + 1 <= pos + delta)
		imm -= delta;
	if (imm < imm_min || imm > imm_max)
		return -ERANGE;
	if (!probe_pass)
		insn->imm = imm;
	return 0;
}
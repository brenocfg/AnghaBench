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
struct bpf_insn {scalar_t__ off; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ S16_MAX ; 
 scalar_t__ S16_MIN ; 

__attribute__((used)) static int bpf_adj_delta_to_off(struct bpf_insn *insn, u32 pos, s32 end_old,
				s32 end_new, s32 curr, const bool probe_pass)
{
	const s32 off_min = S16_MIN, off_max = S16_MAX;
	s32 delta = end_new - end_old;
	s32 off = insn->off;

	if (curr < pos && curr + off + 1 >= end_old)
		off += delta;
	else if (curr >= end_new && curr + off + 1 < end_new)
		off -= delta;
	if (off < off_min || off > off_max)
		return -ERANGE;
	if (!probe_pass)
		insn->off = off;
	return 0;
}
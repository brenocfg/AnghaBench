#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct bpf_prog {TYPE_1__* aux; } ;
struct bpf_line_info {size_t insn_off; } ;
struct TYPE_2__ {size_t nr_linfo; struct bpf_line_info* linfo; } ;

/* Variables and functions */

__attribute__((used)) static void bpf_adj_linfo(struct bpf_prog *prog, u32 off, u32 delta)
{
	struct bpf_line_info *linfo;
	u32 i, nr_linfo;

	nr_linfo = prog->aux->nr_linfo;
	if (!nr_linfo || !delta)
		return;

	linfo = prog->aux->linfo;

	for (i = 0; i < nr_linfo; i++)
		if (off < linfo[i].insn_off)
			break;

	/* Push all off < linfo[i].insn_off by delta */
	for (; i < nr_linfo; i++)
		linfo[i].insn_off += delta;
}
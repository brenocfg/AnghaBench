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
typedef  scalar_t__ u32 ;
struct bpf_verifier_env {struct bpf_prog* prog; } ;
struct bpf_prog {scalar_t__ len; TYPE_1__* aux; } ;
struct bpf_line_info {scalar_t__ insn_off; } ;
struct TYPE_2__ {scalar_t__ nr_linfo; struct bpf_line_info* linfo; } ;

/* Variables and functions */

__attribute__((used)) static const struct bpf_line_info *
find_linfo(const struct bpf_verifier_env *env, u32 insn_off)
{
	const struct bpf_line_info *linfo;
	const struct bpf_prog *prog;
	u32 i, nr_linfo;

	prog = env->prog;
	nr_linfo = prog->aux->nr_linfo;

	if (!nr_linfo || insn_off >= prog->len)
		return NULL;

	linfo = prog->aux->linfo;
	for (i = 1; i < nr_linfo; i++)
		if (insn_off < linfo[i].insn_off)
			break;

	return &linfo[i - 1];
}
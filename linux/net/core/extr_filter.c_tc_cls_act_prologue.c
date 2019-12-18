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
struct bpf_prog {int dummy; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_ACT_SHOT ; 
 int bpf_unclone_prologue (struct bpf_insn*,int,struct bpf_prog const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc_cls_act_prologue(struct bpf_insn *insn_buf, bool direct_write,
			       const struct bpf_prog *prog)
{
	return bpf_unclone_prologue(insn_buf, direct_write, prog, TC_ACT_SHOT);
}
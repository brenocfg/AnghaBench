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
struct bpf_verifier_env {int dummy; } ;
struct bpf_insn {int /*<<< orphan*/  dst_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_OP ; 
 scalar_t__ insn_no_def (struct bpf_insn*) ; 
 int /*<<< orphan*/  is_reg64 (struct bpf_verifier_env*,struct bpf_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool insn_has_def32(struct bpf_verifier_env *env, struct bpf_insn *insn)
{
	if (insn_no_def(insn))
		return false;

	return !is_reg64(env, insn, insn->dst_reg, NULL, DST_OP);
}
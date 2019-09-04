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
typedef  int /*<<< orphan*/  u32 ;
struct bpf_verifier_env {int /*<<< orphan*/  prog; } ;
struct bpf_prog {int /*<<< orphan*/  len; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 scalar_t__ adjust_insn_aux_data (struct bpf_verifier_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_subprog_starts (struct bpf_verifier_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_prog* bpf_patch_insn_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bpf_insn const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bpf_prog *bpf_patch_insn_data(struct bpf_verifier_env *env, u32 off,
					    const struct bpf_insn *patch, u32 len)
{
	struct bpf_prog *new_prog;

	new_prog = bpf_patch_insn_single(env->prog, off, patch, len);
	if (!new_prog)
		return NULL;
	if (adjust_insn_aux_data(env, new_prog->len, off, len))
		return NULL;
	adjust_subprog_starts(env, off, len);
	return new_prog;
}
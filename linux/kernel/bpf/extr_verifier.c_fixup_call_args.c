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
struct bpf_verifier_env {struct bpf_prog* prog; } ;
struct bpf_prog {int len; int /*<<< orphan*/  aux; scalar_t__ jit_requested; struct bpf_insn* insnsi; } ;
struct bpf_insn {int code; scalar_t__ src_reg; } ;

/* Variables and functions */
 int BPF_CALL ; 
 int BPF_JMP ; 
 scalar_t__ BPF_PSEUDO_CALL ; 
 int EFAULT ; 
 int /*<<< orphan*/  bpf_patch_call_args (struct bpf_insn*,int) ; 
 int /*<<< orphan*/  bpf_prog_is_dev_bound (int /*<<< orphan*/ ) ; 
 int get_callee_stack_depth (struct bpf_verifier_env*,struct bpf_insn*,int) ; 
 int jit_subprogs (struct bpf_verifier_env*) ; 

__attribute__((used)) static int fixup_call_args(struct bpf_verifier_env *env)
{
#ifndef CONFIG_BPF_JIT_ALWAYS_ON
	struct bpf_prog *prog = env->prog;
	struct bpf_insn *insn = prog->insnsi;
	int i, depth;
#endif
	int err = 0;

	if (env->prog->jit_requested &&
	    !bpf_prog_is_dev_bound(env->prog->aux)) {
		err = jit_subprogs(env);
		if (err == 0)
			return 0;
		if (err == -EFAULT)
			return err;
	}
#ifndef CONFIG_BPF_JIT_ALWAYS_ON
	for (i = 0; i < prog->len; i++, insn++) {
		if (insn->code != (BPF_JMP | BPF_CALL) ||
		    insn->src_reg != BPF_PSEUDO_CALL)
			continue;
		depth = get_callee_stack_depth(env, insn, i);
		if (depth < 0)
			return depth;
		bpf_patch_call_args(insn, depth);
	}
	err = 0;
#endif
	return err;
}
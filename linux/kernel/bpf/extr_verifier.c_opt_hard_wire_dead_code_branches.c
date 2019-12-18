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
struct bpf_verifier_env {TYPE_1__* prog; struct bpf_insn_aux_data* insn_aux_data; } ;
struct bpf_insn_aux_data {int /*<<< orphan*/  seen; } ;
struct bpf_insn {int off; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  ja ;
struct TYPE_2__ {int len; int /*<<< orphan*/  aux; struct bpf_insn* insnsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_JA ; 
 struct bpf_insn BPF_JMP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bpf_prog_is_dev_bound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_offload_replace_insn (struct bpf_verifier_env*,int,struct bpf_insn*) ; 
 int /*<<< orphan*/  insn_is_cond_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct bpf_insn*,struct bpf_insn*,int) ; 

__attribute__((used)) static void opt_hard_wire_dead_code_branches(struct bpf_verifier_env *env)
{
	struct bpf_insn_aux_data *aux_data = env->insn_aux_data;
	struct bpf_insn ja = BPF_JMP_IMM(BPF_JA, 0, 0, 0);
	struct bpf_insn *insn = env->prog->insnsi;
	const int insn_cnt = env->prog->len;
	int i;

	for (i = 0; i < insn_cnt; i++, insn++) {
		if (!insn_is_cond_jump(insn->code))
			continue;

		if (!aux_data[i + 1].seen)
			ja.off = insn->off;
		else if (!aux_data[i + 1 + insn->off].seen)
			ja.off = 0;
		else
			continue;

		if (bpf_prog_is_dev_bound(env->prog->aux))
			bpf_prog_offload_replace_insn(env, i, &ja);

		memcpy(insn, &ja, sizeof(ja));
	}
}
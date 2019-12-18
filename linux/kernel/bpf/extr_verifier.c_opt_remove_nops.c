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
struct bpf_verifier_env {TYPE_1__* prog; } ;
struct bpf_insn {int dummy; } ;
typedef  int /*<<< orphan*/  ja ;
struct TYPE_2__ {int len; struct bpf_insn* insnsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_JA ; 
 struct bpf_insn BPF_JMP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (struct bpf_insn*,struct bpf_insn const*,int) ; 
 int verifier_remove_insns (struct bpf_verifier_env*,int,int) ; 

__attribute__((used)) static int opt_remove_nops(struct bpf_verifier_env *env)
{
	const struct bpf_insn ja = BPF_JMP_IMM(BPF_JA, 0, 0, 0);
	struct bpf_insn *insn = env->prog->insnsi;
	int insn_cnt = env->prog->len;
	int i, err;

	for (i = 0; i < insn_cnt; i++) {
		if (memcmp(&insn[i], &ja, sizeof(ja)))
			continue;

		err = verifier_remove_insns(env, i, 1);
		if (err)
			return err;
		insn_cnt--;
		i--;
	}

	return 0;
}
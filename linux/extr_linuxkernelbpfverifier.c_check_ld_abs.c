#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct bpf_verifier_env {int subprog_cnt; TYPE_2__* ops; TYPE_1__* prog; } ;
struct bpf_reg_state {scalar_t__ type; } ;
struct bpf_insn {scalar_t__ dst_reg; scalar_t__ off; scalar_t__ src_reg; int /*<<< orphan*/  code; } ;
struct TYPE_4__ {int /*<<< orphan*/  gen_ld_abs; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ BPF_ABS ; 
 scalar_t__ BPF_DW ; 
 scalar_t__ BPF_IND ; 
 scalar_t__ BPF_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_REG_0 ; 
 size_t BPF_REG_6 ; 
 scalar_t__ BPF_SIZE (int /*<<< orphan*/ ) ; 
 int CALLER_SAVED_REGS ; 
 int /*<<< orphan*/  DST_OP_NO_MARK ; 
 int EINVAL ; 
 scalar_t__ PTR_TO_CTX ; 
 int /*<<< orphan*/  SRC_OP ; 
 size_t* caller_saved ; 
 int check_reg_arg (struct bpf_verifier_env*,size_t,int /*<<< orphan*/ ) ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 int /*<<< orphan*/  mark_reg_not_init (struct bpf_verifier_env*,struct bpf_reg_state*,size_t) ; 
 int /*<<< orphan*/  mark_reg_unknown (struct bpf_verifier_env*,struct bpf_reg_state*,scalar_t__) ; 
 int /*<<< orphan*/  may_access_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*) ; 

__attribute__((used)) static int check_ld_abs(struct bpf_verifier_env *env, struct bpf_insn *insn)
{
	struct bpf_reg_state *regs = cur_regs(env);
	u8 mode = BPF_MODE(insn->code);
	int i, err;

	if (!may_access_skb(env->prog->type)) {
		verbose(env, "BPF_LD_[ABS|IND] instructions not allowed for this program type\n");
		return -EINVAL;
	}

	if (!env->ops->gen_ld_abs) {
		verbose(env, "bpf verifier is misconfigured\n");
		return -EINVAL;
	}

	if (env->subprog_cnt > 1) {
		/* when program has LD_ABS insn JITs and interpreter assume
		 * that r1 == ctx == skb which is not the case for callees
		 * that can have arbitrary arguments. It's problematic
		 * for main prog as well since JITs would need to analyze
		 * all functions in order to make proper register save/restore
		 * decisions in the main prog. Hence disallow LD_ABS with calls
		 */
		verbose(env, "BPF_LD_[ABS|IND] instructions cannot be mixed with bpf-to-bpf calls\n");
		return -EINVAL;
	}

	if (insn->dst_reg != BPF_REG_0 || insn->off != 0 ||
	    BPF_SIZE(insn->code) == BPF_DW ||
	    (mode == BPF_ABS && insn->src_reg != BPF_REG_0)) {
		verbose(env, "BPF_LD_[ABS|IND] uses reserved fields\n");
		return -EINVAL;
	}

	/* check whether implicit source operand (register R6) is readable */
	err = check_reg_arg(env, BPF_REG_6, SRC_OP);
	if (err)
		return err;

	if (regs[BPF_REG_6].type != PTR_TO_CTX) {
		verbose(env,
			"at the time of BPF_LD_ABS|IND R6 != pointer to skb\n");
		return -EINVAL;
	}

	if (mode == BPF_IND) {
		/* check explicit source operand */
		err = check_reg_arg(env, insn->src_reg, SRC_OP);
		if (err)
			return err;
	}

	/* reset caller saved regs to unreadable */
	for (i = 0; i < CALLER_SAVED_REGS; i++) {
		mark_reg_not_init(env, regs, caller_saved[i]);
		check_reg_arg(env, caller_saved[i], DST_OP_NO_MARK);
	}

	/* mark destination R0 register as readable, since it contains
	 * the value fetched from the packet.
	 * Already marked as written above.
	 */
	mark_reg_unknown(env, regs, BPF_REG_0);
	return 0;
}
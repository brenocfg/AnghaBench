#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct bpf_verifier_state {size_t curframe; int speculative; int branches; scalar_t__ active_spin_lock; void** frame; } ;
struct TYPE_7__ {int level; } ;
struct bpf_verifier_env {int prev_insn_idx; int insn_idx; scalar_t__ insn_processed; TYPE_4__* subprog_info; TYPE_3__* prog; TYPE_2__* insn_aux_data; struct bpf_verifier_state* cur_state; int /*<<< orphan*/  jmps_processed; int /*<<< orphan*/  allow_ptr_leaks; TYPE_1__ log; int /*<<< orphan*/ * prev_linfo; } ;
struct bpf_reg_state {int type; } ;
struct bpf_insn_cbs {struct bpf_verifier_env* private_data; int /*<<< orphan*/  (* cb_print ) (struct bpf_verifier_env*,char*,scalar_t__) ;} ;
struct bpf_insn {int src_reg; int dst_reg; scalar_t__ off; scalar_t__ imm; int /*<<< orphan*/  code; } ;
struct bpf_func_state {int dummy; } ;
typedef  enum bpf_reg_type { ____Placeholder_bpf_reg_type } bpf_reg_type ;
struct TYPE_12__ {int /*<<< orphan*/  stack_depth; } ;
struct TYPE_11__ {size_t type; } ;
struct TYPE_10__ {int /*<<< orphan*/  stack_depth; } ;
struct TYPE_9__ {int len; TYPE_6__* aux; struct bpf_insn* insnsi; } ;
struct TYPE_8__ {int seen; int ptr_type; } ;

/* Variables and functions */
 scalar_t__ BPF_ABS ; 
 scalar_t__ BPF_ALU ; 
 scalar_t__ BPF_ALU64 ; 
 scalar_t__ BPF_CALL ; 
 scalar_t__ BPF_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_COMPLEXITY_LIMIT_INSNS ; 
 scalar_t__ BPF_EXIT ; 
 scalar_t__ BPF_FUNC_spin_unlock ; 
 scalar_t__ BPF_IMM ; 
 scalar_t__ BPF_IND ; 
 scalar_t__ BPF_JA ; 
 scalar_t__ BPF_JMP ; 
 scalar_t__ BPF_JMP32 ; 
 scalar_t__ BPF_K ; 
 scalar_t__ BPF_LD ; 
 scalar_t__ BPF_LDX ; 
 int BPF_LOG_LEVEL ; 
 int BPF_LOG_LEVEL2 ; 
 int /*<<< orphan*/  BPF_MAIN_FUNC ; 
 scalar_t__ BPF_MEM ; 
 scalar_t__ BPF_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_OP (int /*<<< orphan*/ ) ; 
 int BPF_PSEUDO_CALL ; 
 int /*<<< orphan*/  BPF_READ ; 
 int BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_ST ; 
 scalar_t__ BPF_STX ; 
 int /*<<< orphan*/  BPF_WRITE ; 
 scalar_t__ BPF_XADD ; 
 int /*<<< orphan*/  DST_OP_NO_MARK ; 
 int E2BIG ; 
 int EACCES ; 
 int EAGAIN ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NOT_INIT ; 
 int /*<<< orphan*/  SRC_OP ; 
 scalar_t__ bpf_prog_is_dev_bound (TYPE_6__*) ; 
 int bpf_prog_offload_verify_insn (struct bpf_verifier_env*,scalar_t__,int) ; 
 int check_alu_op (struct bpf_verifier_env*,struct bpf_insn*) ; 
 int check_cond_jmp_op (struct bpf_verifier_env*,struct bpf_insn*,int*) ; 
 int check_func_call (struct bpf_verifier_env*,struct bpf_insn*,int*) ; 
 int check_helper_call (struct bpf_verifier_env*,scalar_t__,int) ; 
 int check_ld_abs (struct bpf_verifier_env*,struct bpf_insn*) ; 
 int check_ld_imm (struct bpf_verifier_env*,struct bpf_insn*) ; 
 int check_mem_access (struct bpf_verifier_env*,int,size_t,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int check_reference_leak (struct bpf_verifier_env*) ; 
 int check_reg_arg (struct bpf_verifier_env*,int,int /*<<< orphan*/ ) ; 
 int check_return_code (struct bpf_verifier_env*) ; 
 int check_xadd (struct bpf_verifier_env*,size_t,struct bpf_insn*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_func_state (struct bpf_verifier_env*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ctx_reg (struct bpf_verifier_env*,int) ; 
 scalar_t__ is_pointer_value (struct bpf_verifier_env*,int) ; 
 int is_state_visited (struct bpf_verifier_env*,size_t) ; 
 int /*<<< orphan*/  kfree (struct bpf_verifier_state*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ need_resched () ; 
 int pop_stack (struct bpf_verifier_env*,int*,int*) ; 
 int prepare_func_exit (struct bpf_verifier_env*,int*) ; 
 int /*<<< orphan*/  print_bpf_insn (struct bpf_insn_cbs const*,struct bpf_insn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_verifier_state (struct bpf_verifier_env*,void*) ; 
 TYPE_5__* reg_state (struct bpf_verifier_env*,int) ; 
 scalar_t__ reg_type_mismatch (int,int) ; 
 int /*<<< orphan*/ * reg_type_str ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_branch_counts (struct bpf_verifier_env*,struct bpf_verifier_state*) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 
 int /*<<< orphan*/  verbose_linfo (struct bpf_verifier_env*,scalar_t__,char*) ; 

__attribute__((used)) static int do_check(struct bpf_verifier_env *env)
{
	struct bpf_verifier_state *state;
	struct bpf_insn *insns = env->prog->insnsi;
	struct bpf_reg_state *regs;
	int insn_cnt = env->prog->len;
	bool do_print_state = false;
	int prev_insn_idx = -1;

	env->prev_linfo = NULL;

	state = kzalloc(sizeof(struct bpf_verifier_state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;
	state->curframe = 0;
	state->speculative = false;
	state->branches = 1;
	state->frame[0] = kzalloc(sizeof(struct bpf_func_state), GFP_KERNEL);
	if (!state->frame[0]) {
		kfree(state);
		return -ENOMEM;
	}
	env->cur_state = state;
	init_func_state(env, state->frame[0],
			BPF_MAIN_FUNC /* callsite */,
			0 /* frameno */,
			0 /* subprogno, zero == main subprog */);

	for (;;) {
		struct bpf_insn *insn;
		u8 class;
		int err;

		env->prev_insn_idx = prev_insn_idx;
		if (env->insn_idx >= insn_cnt) {
			verbose(env, "invalid insn idx %d insn_cnt %d\n",
				env->insn_idx, insn_cnt);
			return -EFAULT;
		}

		insn = &insns[env->insn_idx];
		class = BPF_CLASS(insn->code);

		if (++env->insn_processed > BPF_COMPLEXITY_LIMIT_INSNS) {
			verbose(env,
				"BPF program is too large. Processed %d insn\n",
				env->insn_processed);
			return -E2BIG;
		}

		err = is_state_visited(env, env->insn_idx);
		if (err < 0)
			return err;
		if (err == 1) {
			/* found equivalent state, can prune the search */
			if (env->log.level & BPF_LOG_LEVEL) {
				if (do_print_state)
					verbose(env, "\nfrom %d to %d%s: safe\n",
						env->prev_insn_idx, env->insn_idx,
						env->cur_state->speculative ?
						" (speculative execution)" : "");
				else
					verbose(env, "%d: safe\n", env->insn_idx);
			}
			goto process_bpf_exit;
		}

		if (signal_pending(current))
			return -EAGAIN;

		if (need_resched())
			cond_resched();

		if (env->log.level & BPF_LOG_LEVEL2 ||
		    (env->log.level & BPF_LOG_LEVEL && do_print_state)) {
			if (env->log.level & BPF_LOG_LEVEL2)
				verbose(env, "%d:", env->insn_idx);
			else
				verbose(env, "\nfrom %d to %d%s:",
					env->prev_insn_idx, env->insn_idx,
					env->cur_state->speculative ?
					" (speculative execution)" : "");
			print_verifier_state(env, state->frame[state->curframe]);
			do_print_state = false;
		}

		if (env->log.level & BPF_LOG_LEVEL) {
			const struct bpf_insn_cbs cbs = {
				.cb_print	= verbose,
				.private_data	= env,
			};

			verbose_linfo(env, env->insn_idx, "; ");
			verbose(env, "%d: ", env->insn_idx);
			print_bpf_insn(&cbs, insn, env->allow_ptr_leaks);
		}

		if (bpf_prog_is_dev_bound(env->prog->aux)) {
			err = bpf_prog_offload_verify_insn(env, env->insn_idx,
							   env->prev_insn_idx);
			if (err)
				return err;
		}

		regs = cur_regs(env);
		env->insn_aux_data[env->insn_idx].seen = true;
		prev_insn_idx = env->insn_idx;

		if (class == BPF_ALU || class == BPF_ALU64) {
			err = check_alu_op(env, insn);
			if (err)
				return err;

		} else if (class == BPF_LDX) {
			enum bpf_reg_type *prev_src_type, src_reg_type;

			/* check for reserved fields is already done */

			/* check src operand */
			err = check_reg_arg(env, insn->src_reg, SRC_OP);
			if (err)
				return err;

			err = check_reg_arg(env, insn->dst_reg, DST_OP_NO_MARK);
			if (err)
				return err;

			src_reg_type = regs[insn->src_reg].type;

			/* check that memory (src_reg + off) is readable,
			 * the state of dst_reg will be updated by this func
			 */
			err = check_mem_access(env, env->insn_idx, insn->src_reg,
					       insn->off, BPF_SIZE(insn->code),
					       BPF_READ, insn->dst_reg, false);
			if (err)
				return err;

			prev_src_type = &env->insn_aux_data[env->insn_idx].ptr_type;

			if (*prev_src_type == NOT_INIT) {
				/* saw a valid insn
				 * dst_reg = *(u32 *)(src_reg + off)
				 * save type to validate intersecting paths
				 */
				*prev_src_type = src_reg_type;

			} else if (reg_type_mismatch(src_reg_type, *prev_src_type)) {
				/* ABuser program is trying to use the same insn
				 * dst_reg = *(u32*) (src_reg + off)
				 * with different pointer types:
				 * src_reg == ctx in one branch and
				 * src_reg == stack|map in some other branch.
				 * Reject it.
				 */
				verbose(env, "same insn cannot be used with different pointers\n");
				return -EINVAL;
			}

		} else if (class == BPF_STX) {
			enum bpf_reg_type *prev_dst_type, dst_reg_type;

			if (BPF_MODE(insn->code) == BPF_XADD) {
				err = check_xadd(env, env->insn_idx, insn);
				if (err)
					return err;
				env->insn_idx++;
				continue;
			}

			/* check src1 operand */
			err = check_reg_arg(env, insn->src_reg, SRC_OP);
			if (err)
				return err;
			/* check src2 operand */
			err = check_reg_arg(env, insn->dst_reg, SRC_OP);
			if (err)
				return err;

			dst_reg_type = regs[insn->dst_reg].type;

			/* check that memory (dst_reg + off) is writeable */
			err = check_mem_access(env, env->insn_idx, insn->dst_reg,
					       insn->off, BPF_SIZE(insn->code),
					       BPF_WRITE, insn->src_reg, false);
			if (err)
				return err;

			prev_dst_type = &env->insn_aux_data[env->insn_idx].ptr_type;

			if (*prev_dst_type == NOT_INIT) {
				*prev_dst_type = dst_reg_type;
			} else if (reg_type_mismatch(dst_reg_type, *prev_dst_type)) {
				verbose(env, "same insn cannot be used with different pointers\n");
				return -EINVAL;
			}

		} else if (class == BPF_ST) {
			if (BPF_MODE(insn->code) != BPF_MEM ||
			    insn->src_reg != BPF_REG_0) {
				verbose(env, "BPF_ST uses reserved fields\n");
				return -EINVAL;
			}
			/* check src operand */
			err = check_reg_arg(env, insn->dst_reg, SRC_OP);
			if (err)
				return err;

			if (is_ctx_reg(env, insn->dst_reg)) {
				verbose(env, "BPF_ST stores into R%d %s is not allowed\n",
					insn->dst_reg,
					reg_type_str[reg_state(env, insn->dst_reg)->type]);
				return -EACCES;
			}

			/* check that memory (dst_reg + off) is writeable */
			err = check_mem_access(env, env->insn_idx, insn->dst_reg,
					       insn->off, BPF_SIZE(insn->code),
					       BPF_WRITE, -1, false);
			if (err)
				return err;

		} else if (class == BPF_JMP || class == BPF_JMP32) {
			u8 opcode = BPF_OP(insn->code);

			env->jmps_processed++;
			if (opcode == BPF_CALL) {
				if (BPF_SRC(insn->code) != BPF_K ||
				    insn->off != 0 ||
				    (insn->src_reg != BPF_REG_0 &&
				     insn->src_reg != BPF_PSEUDO_CALL) ||
				    insn->dst_reg != BPF_REG_0 ||
				    class == BPF_JMP32) {
					verbose(env, "BPF_CALL uses reserved fields\n");
					return -EINVAL;
				}

				if (env->cur_state->active_spin_lock &&
				    (insn->src_reg == BPF_PSEUDO_CALL ||
				     insn->imm != BPF_FUNC_spin_unlock)) {
					verbose(env, "function calls are not allowed while holding a lock\n");
					return -EINVAL;
				}
				if (insn->src_reg == BPF_PSEUDO_CALL)
					err = check_func_call(env, insn, &env->insn_idx);
				else
					err = check_helper_call(env, insn->imm, env->insn_idx);
				if (err)
					return err;

			} else if (opcode == BPF_JA) {
				if (BPF_SRC(insn->code) != BPF_K ||
				    insn->imm != 0 ||
				    insn->src_reg != BPF_REG_0 ||
				    insn->dst_reg != BPF_REG_0 ||
				    class == BPF_JMP32) {
					verbose(env, "BPF_JA uses reserved fields\n");
					return -EINVAL;
				}

				env->insn_idx += insn->off + 1;
				continue;

			} else if (opcode == BPF_EXIT) {
				if (BPF_SRC(insn->code) != BPF_K ||
				    insn->imm != 0 ||
				    insn->src_reg != BPF_REG_0 ||
				    insn->dst_reg != BPF_REG_0 ||
				    class == BPF_JMP32) {
					verbose(env, "BPF_EXIT uses reserved fields\n");
					return -EINVAL;
				}

				if (env->cur_state->active_spin_lock) {
					verbose(env, "bpf_spin_unlock is missing\n");
					return -EINVAL;
				}

				if (state->curframe) {
					/* exit from nested function */
					err = prepare_func_exit(env, &env->insn_idx);
					if (err)
						return err;
					do_print_state = true;
					continue;
				}

				err = check_reference_leak(env);
				if (err)
					return err;

				/* eBPF calling convetion is such that R0 is used
				 * to return the value from eBPF program.
				 * Make sure that it's readable at this time
				 * of bpf_exit, which means that program wrote
				 * something into it earlier
				 */
				err = check_reg_arg(env, BPF_REG_0, SRC_OP);
				if (err)
					return err;

				if (is_pointer_value(env, BPF_REG_0)) {
					verbose(env, "R0 leaks addr as return value\n");
					return -EACCES;
				}

				err = check_return_code(env);
				if (err)
					return err;
process_bpf_exit:
				update_branch_counts(env, env->cur_state);
				err = pop_stack(env, &prev_insn_idx,
						&env->insn_idx);
				if (err < 0) {
					if (err != -ENOENT)
						return err;
					break;
				} else {
					do_print_state = true;
					continue;
				}
			} else {
				err = check_cond_jmp_op(env, insn, &env->insn_idx);
				if (err)
					return err;
			}
		} else if (class == BPF_LD) {
			u8 mode = BPF_MODE(insn->code);

			if (mode == BPF_ABS || mode == BPF_IND) {
				err = check_ld_abs(env, insn);
				if (err)
					return err;

			} else if (mode == BPF_IMM) {
				err = check_ld_imm(env, insn);
				if (err)
					return err;

				env->insn_idx++;
				env->insn_aux_data[env->insn_idx].seen = true;
			} else {
				verbose(env, "invalid BPF_LD mode\n");
				return -EINVAL;
			}
		} else {
			verbose(env, "unknown insn class %d\n", class);
			return -EINVAL;
		}

		env->insn_idx++;
	}

	env->prog->aux->stack_depth = env->subprog_info[0].stack_depth;
	return 0;
}
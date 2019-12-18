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
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct TYPE_4__ {int level; } ;
struct bpf_verifier_env {int /*<<< orphan*/  allow_ptr_leaks; TYPE_2__ log; TYPE_1__* prog; } ;
struct bpf_insn_cbs {struct bpf_verifier_env* private_data; int /*<<< orphan*/  (* cb_print ) (struct bpf_verifier_env*,char*,int) ;} ;
struct bpf_insn {scalar_t__ code; unsigned int dst_reg; unsigned int src_reg; int off; } ;
struct TYPE_3__ {struct bpf_insn* insnsi; } ;

/* Variables and functions */
 scalar_t__ BPF_ABS ; 
 scalar_t__ BPF_ALU ; 
 scalar_t__ BPF_ALU64 ; 
 scalar_t__ BPF_CALL ; 
 scalar_t__ BPF_CLASS (scalar_t__) ; 
 scalar_t__ BPF_DW ; 
 scalar_t__ BPF_EXIT ; 
 scalar_t__ BPF_IND ; 
 scalar_t__ BPF_JMP ; 
 scalar_t__ BPF_JMP32 ; 
 scalar_t__ BPF_LD ; 
 scalar_t__ BPF_LDX ; 
 int BPF_LOG_LEVEL ; 
 scalar_t__ BPF_MODE (scalar_t__) ; 
 scalar_t__ BPF_MOV ; 
 scalar_t__ BPF_OP (scalar_t__) ; 
 unsigned int BPF_PSEUDO_CALL ; 
 unsigned int BPF_REG_FP ; 
 int BPF_REG_SIZE ; 
 scalar_t__ BPF_SIZE (scalar_t__) ; 
 scalar_t__ BPF_SRC (scalar_t__) ; 
 scalar_t__ BPF_ST ; 
 scalar_t__ BPF_STX ; 
 scalar_t__ BPF_X ; 
 int EFAULT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  print_bpf_insn (struct bpf_insn_cbs const*,struct bpf_insn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,int,...) ; 

__attribute__((used)) static int backtrack_insn(struct bpf_verifier_env *env, int idx,
			  u32 *reg_mask, u64 *stack_mask)
{
	const struct bpf_insn_cbs cbs = {
		.cb_print	= verbose,
		.private_data	= env,
	};
	struct bpf_insn *insn = env->prog->insnsi + idx;
	u8 class = BPF_CLASS(insn->code);
	u8 opcode = BPF_OP(insn->code);
	u8 mode = BPF_MODE(insn->code);
	u32 dreg = 1u << insn->dst_reg;
	u32 sreg = 1u << insn->src_reg;
	u32 spi;

	if (insn->code == 0)
		return 0;
	if (env->log.level & BPF_LOG_LEVEL) {
		verbose(env, "regs=%x stack=%llx before ", *reg_mask, *stack_mask);
		verbose(env, "%d: ", idx);
		print_bpf_insn(&cbs, insn, env->allow_ptr_leaks);
	}

	if (class == BPF_ALU || class == BPF_ALU64) {
		if (!(*reg_mask & dreg))
			return 0;
		if (opcode == BPF_MOV) {
			if (BPF_SRC(insn->code) == BPF_X) {
				/* dreg = sreg
				 * dreg needs precision after this insn
				 * sreg needs precision before this insn
				 */
				*reg_mask &= ~dreg;
				*reg_mask |= sreg;
			} else {
				/* dreg = K
				 * dreg needs precision after this insn.
				 * Corresponding register is already marked
				 * as precise=true in this verifier state.
				 * No further markings in parent are necessary
				 */
				*reg_mask &= ~dreg;
			}
		} else {
			if (BPF_SRC(insn->code) == BPF_X) {
				/* dreg += sreg
				 * both dreg and sreg need precision
				 * before this insn
				 */
				*reg_mask |= sreg;
			} /* else dreg += K
			   * dreg still needs precision before this insn
			   */
		}
	} else if (class == BPF_LDX) {
		if (!(*reg_mask & dreg))
			return 0;
		*reg_mask &= ~dreg;

		/* scalars can only be spilled into stack w/o losing precision.
		 * Load from any other memory can be zero extended.
		 * The desire to keep that precision is already indicated
		 * by 'precise' mark in corresponding register of this state.
		 * No further tracking necessary.
		 */
		if (insn->src_reg != BPF_REG_FP)
			return 0;
		if (BPF_SIZE(insn->code) != BPF_DW)
			return 0;

		/* dreg = *(u64 *)[fp - off] was a fill from the stack.
		 * that [fp - off] slot contains scalar that needs to be
		 * tracked with precision
		 */
		spi = (-insn->off - 1) / BPF_REG_SIZE;
		if (spi >= 64) {
			verbose(env, "BUG spi %d\n", spi);
			WARN_ONCE(1, "verifier backtracking bug");
			return -EFAULT;
		}
		*stack_mask |= 1ull << spi;
	} else if (class == BPF_STX || class == BPF_ST) {
		if (*reg_mask & dreg)
			/* stx & st shouldn't be using _scalar_ dst_reg
			 * to access memory. It means backtracking
			 * encountered a case of pointer subtraction.
			 */
			return -ENOTSUPP;
		/* scalars can only be spilled into stack */
		if (insn->dst_reg != BPF_REG_FP)
			return 0;
		if (BPF_SIZE(insn->code) != BPF_DW)
			return 0;
		spi = (-insn->off - 1) / BPF_REG_SIZE;
		if (spi >= 64) {
			verbose(env, "BUG spi %d\n", spi);
			WARN_ONCE(1, "verifier backtracking bug");
			return -EFAULT;
		}
		if (!(*stack_mask & (1ull << spi)))
			return 0;
		*stack_mask &= ~(1ull << spi);
		if (class == BPF_STX)
			*reg_mask |= sreg;
	} else if (class == BPF_JMP || class == BPF_JMP32) {
		if (opcode == BPF_CALL) {
			if (insn->src_reg == BPF_PSEUDO_CALL)
				return -ENOTSUPP;
			/* regular helper call sets R0 */
			*reg_mask &= ~1;
			if (*reg_mask & 0x3f) {
				/* if backtracing was looking for registers R1-R5
				 * they should have been found already.
				 */
				verbose(env, "BUG regs %x\n", *reg_mask);
				WARN_ONCE(1, "verifier backtracking bug");
				return -EFAULT;
			}
		} else if (opcode == BPF_EXIT) {
			return -ENOTSUPP;
		}
	} else if (class == BPF_LD) {
		if (!(*reg_mask & dreg))
			return 0;
		*reg_mask &= ~dreg;
		/* It's ld_imm64 or ld_abs or ld_ind.
		 * For ld_imm64 no further tracking of precision
		 * into parent is necessary
		 */
		if (mode == BPF_IND || mode == BPF_ABS)
			/* to be analyzed */
			return -ENOTSUPP;
	}
	return 0;
}
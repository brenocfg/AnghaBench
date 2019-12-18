#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_7__ {int value; int mask; } ;
struct bpf_reg_state {void* smax_value; void* smin_value; void* umax_value; void* umin_value; TYPE_1__ var_off; } ;
typedef  int s64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
#define  BPF_JEQ 138 
#define  BPF_JGE 137 
#define  BPF_JGT 136 
#define  BPF_JLE 135 
#define  BPF_JLT 134 
#define  BPF_JNE 133 
#define  BPF_JSET 132 
#define  BPF_JSGE 131 
#define  BPF_JSGT 130 
#define  BPF_JSLE 129 
#define  BPF_JSLT 128 
 scalar_t__ __is_pointer_value (int,struct bpf_reg_state*) ; 
 int /*<<< orphan*/  __mark_reg_known (struct bpf_reg_state*,int) ; 
 int /*<<< orphan*/  __reg_bound_offset (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  __reg_deduce_bounds (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  __update_reg_bounds (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  cmp_val_with_extended_s64 (int,struct bpf_reg_state*) ; 
 int gen_hi_max (TYPE_1__) ; 
 int gen_hi_min (TYPE_1__) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 void* max (void*,int) ; 
 void* min (void*,int) ; 
 TYPE_1__ tnum_and (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnum_const (int) ; 
 TYPE_1__ tnum_or (TYPE_1__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_set_min_max(struct bpf_reg_state *true_reg,
			    struct bpf_reg_state *false_reg, u64 val,
			    u8 opcode, bool is_jmp32)
{
	s64 sval;

	/* If the dst_reg is a pointer, we can't learn anything about its
	 * variable offset from the compare (unless src_reg were a pointer into
	 * the same object, but we don't bother with that.
	 * Since false_reg and true_reg have the same type by construction, we
	 * only need to check one of them for pointerness.
	 */
	if (__is_pointer_value(false, false_reg))
		return;

	val = is_jmp32 ? (u32)val : val;
	sval = is_jmp32 ? (s64)(s32)val : (s64)val;

	switch (opcode) {
	case BPF_JEQ:
	case BPF_JNE:
	{
		struct bpf_reg_state *reg =
			opcode == BPF_JEQ ? true_reg : false_reg;

		/* For BPF_JEQ, if this is false we know nothing Jon Snow, but
		 * if it is true we know the value for sure. Likewise for
		 * BPF_JNE.
		 */
		if (is_jmp32) {
			u64 old_v = reg->var_off.value;
			u64 hi_mask = ~0xffffffffULL;

			reg->var_off.value = (old_v & hi_mask) | val;
			reg->var_off.mask &= hi_mask;
		} else {
			__mark_reg_known(reg, val);
		}
		break;
	}
	case BPF_JSET:
		false_reg->var_off = tnum_and(false_reg->var_off,
					      tnum_const(~val));
		if (is_power_of_2(val))
			true_reg->var_off = tnum_or(true_reg->var_off,
						    tnum_const(val));
		break;
	case BPF_JGE:
	case BPF_JGT:
	{
		u64 false_umax = opcode == BPF_JGT ? val    : val - 1;
		u64 true_umin = opcode == BPF_JGT ? val + 1 : val;

		if (is_jmp32) {
			false_umax += gen_hi_max(false_reg->var_off);
			true_umin += gen_hi_min(true_reg->var_off);
		}
		false_reg->umax_value = min(false_reg->umax_value, false_umax);
		true_reg->umin_value = max(true_reg->umin_value, true_umin);
		break;
	}
	case BPF_JSGE:
	case BPF_JSGT:
	{
		s64 false_smax = opcode == BPF_JSGT ? sval    : sval - 1;
		s64 true_smin = opcode == BPF_JSGT ? sval + 1 : sval;

		/* If the full s64 was not sign-extended from s32 then don't
		 * deduct further info.
		 */
		if (is_jmp32 && !cmp_val_with_extended_s64(sval, false_reg))
			break;
		false_reg->smax_value = min(false_reg->smax_value, false_smax);
		true_reg->smin_value = max(true_reg->smin_value, true_smin);
		break;
	}
	case BPF_JLE:
	case BPF_JLT:
	{
		u64 false_umin = opcode == BPF_JLT ? val    : val + 1;
		u64 true_umax = opcode == BPF_JLT ? val - 1 : val;

		if (is_jmp32) {
			false_umin += gen_hi_min(false_reg->var_off);
			true_umax += gen_hi_max(true_reg->var_off);
		}
		false_reg->umin_value = max(false_reg->umin_value, false_umin);
		true_reg->umax_value = min(true_reg->umax_value, true_umax);
		break;
	}
	case BPF_JSLE:
	case BPF_JSLT:
	{
		s64 false_smin = opcode == BPF_JSLT ? sval    : sval + 1;
		s64 true_smax = opcode == BPF_JSLT ? sval - 1 : sval;

		if (is_jmp32 && !cmp_val_with_extended_s64(sval, false_reg))
			break;
		false_reg->smin_value = max(false_reg->smin_value, false_smin);
		true_reg->smax_value = min(true_reg->smax_value, true_smax);
		break;
	}
	default:
		break;
	}

	__reg_deduce_bounds(false_reg);
	__reg_deduce_bounds(true_reg);
	/* We might have learned some bits from the bounds. */
	__reg_bound_offset(false_reg);
	__reg_bound_offset(true_reg);
	/* Intersecting with the old var_off might have improved our bounds
	 * slightly.  e.g. if umax was 0x7f...f and var_off was (0; 0xf...fc),
	 * then new var_off is (0; 0x7f...fc) which improves our umax.
	 */
	__update_reg_bounds(false_reg);
	__update_reg_bounds(true_reg);
}
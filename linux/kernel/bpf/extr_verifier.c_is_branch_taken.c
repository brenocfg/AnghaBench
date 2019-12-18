#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {int mask; int value; } ;
struct bpf_reg_state {unsigned long long umax_value; unsigned long long umin_value; scalar_t__ smin_value; scalar_t__ smax_value; TYPE_1__ var_off; } ;
typedef  scalar_t__ s64 ;
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
 scalar_t__ S32_MAX ; 
 scalar_t__ S32_MIN ; 
 scalar_t__ __is_pointer_value (int,struct bpf_reg_state*) ; 
 int /*<<< orphan*/  coerce_reg_to_size (struct bpf_reg_state*,int) ; 
 int /*<<< orphan*/  tnum_equals_const (TYPE_1__,int) ; 
 int /*<<< orphan*/  tnum_is_const (TYPE_1__) ; 

__attribute__((used)) static int is_branch_taken(struct bpf_reg_state *reg, u64 val, u8 opcode,
			   bool is_jmp32)
{
	struct bpf_reg_state reg_lo;
	s64 sval;

	if (__is_pointer_value(false, reg))
		return -1;

	if (is_jmp32) {
		reg_lo = *reg;
		reg = &reg_lo;
		/* For JMP32, only low 32 bits are compared, coerce_reg_to_size
		 * could truncate high bits and update umin/umax according to
		 * information of low bits.
		 */
		coerce_reg_to_size(reg, 4);
		/* smin/smax need special handling. For example, after coerce,
		 * if smin_value is 0x00000000ffffffffLL, the value is -1 when
		 * used as operand to JMP32. It is a negative number from s32's
		 * point of view, while it is a positive number when seen as
		 * s64. The smin/smax are kept as s64, therefore, when used with
		 * JMP32, they need to be transformed into s32, then sign
		 * extended back to s64.
		 *
		 * Also, smin/smax were copied from umin/umax. If umin/umax has
		 * different sign bit, then min/max relationship doesn't
		 * maintain after casting into s32, for this case, set smin/smax
		 * to safest range.
		 */
		if ((reg->umax_value ^ reg->umin_value) &
		    (1ULL << 31)) {
			reg->smin_value = S32_MIN;
			reg->smax_value = S32_MAX;
		}
		reg->smin_value = (s64)(s32)reg->smin_value;
		reg->smax_value = (s64)(s32)reg->smax_value;

		val = (u32)val;
		sval = (s64)(s32)val;
	} else {
		sval = (s64)val;
	}

	switch (opcode) {
	case BPF_JEQ:
		if (tnum_is_const(reg->var_off))
			return !!tnum_equals_const(reg->var_off, val);
		break;
	case BPF_JNE:
		if (tnum_is_const(reg->var_off))
			return !tnum_equals_const(reg->var_off, val);
		break;
	case BPF_JSET:
		if ((~reg->var_off.mask & reg->var_off.value) & val)
			return 1;
		if (!((reg->var_off.mask | reg->var_off.value) & val))
			return 0;
		break;
	case BPF_JGT:
		if (reg->umin_value > val)
			return 1;
		else if (reg->umax_value <= val)
			return 0;
		break;
	case BPF_JSGT:
		if (reg->smin_value > sval)
			return 1;
		else if (reg->smax_value < sval)
			return 0;
		break;
	case BPF_JLT:
		if (reg->umax_value < val)
			return 1;
		else if (reg->umin_value >= val)
			return 0;
		break;
	case BPF_JSLT:
		if (reg->smax_value < sval)
			return 1;
		else if (reg->smin_value >= sval)
			return 0;
		break;
	case BPF_JGE:
		if (reg->umin_value >= val)
			return 1;
		else if (reg->umax_value < val)
			return 0;
		break;
	case BPF_JSGE:
		if (reg->smin_value >= sval)
			return 1;
		else if (reg->smax_value < sval)
			return 0;
		break;
	case BPF_JLE:
		if (reg->umax_value <= val)
			return 1;
		else if (reg->umin_value > val)
			return 0;
		break;
	case BPF_JSLE:
		if (reg->smax_value <= sval)
			return 1;
		else if (reg->smin_value > sval)
			return 0;
		break;
	}

	return -1;
}
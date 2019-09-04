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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct bpf_reg_state {int /*<<< orphan*/  smin_value; int /*<<< orphan*/  smax_value; int /*<<< orphan*/  umin_value; int /*<<< orphan*/  umax_value; int /*<<< orphan*/  var_off; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
#define  BPF_JEQ 137 
#define  BPF_JGE 136 
#define  BPF_JGT 135 
#define  BPF_JLE 134 
#define  BPF_JLT 133 
#define  BPF_JNE 132 
#define  BPF_JSGE 131 
#define  BPF_JSGT 130 
#define  BPF_JSLE 129 
#define  BPF_JSLT 128 
 scalar_t__ __is_pointer_value (int,struct bpf_reg_state*) ; 
 int /*<<< orphan*/  tnum_equals_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnum_is_const (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_branch_taken(struct bpf_reg_state *reg, u64 val, u8 opcode)
{
	if (__is_pointer_value(false, reg))
		return -1;

	switch (opcode) {
	case BPF_JEQ:
		if (tnum_is_const(reg->var_off))
			return !!tnum_equals_const(reg->var_off, val);
		break;
	case BPF_JNE:
		if (tnum_is_const(reg->var_off))
			return !tnum_equals_const(reg->var_off, val);
		break;
	case BPF_JGT:
		if (reg->umin_value > val)
			return 1;
		else if (reg->umax_value <= val)
			return 0;
		break;
	case BPF_JSGT:
		if (reg->smin_value > (s64)val)
			return 1;
		else if (reg->smax_value < (s64)val)
			return 0;
		break;
	case BPF_JLT:
		if (reg->umax_value < val)
			return 1;
		else if (reg->umin_value >= val)
			return 0;
		break;
	case BPF_JSLT:
		if (reg->smax_value < (s64)val)
			return 1;
		else if (reg->smin_value >= (s64)val)
			return 0;
		break;
	case BPF_JGE:
		if (reg->umin_value >= val)
			return 1;
		else if (reg->umax_value < val)
			return 0;
		break;
	case BPF_JSGE:
		if (reg->smin_value >= (s64)val)
			return 1;
		else if (reg->smax_value < (s64)val)
			return 0;
		break;
	case BPF_JLE:
		if (reg->umax_value <= val)
			return 1;
		else if (reg->umin_value > val)
			return 0;
		break;
	case BPF_JSLE:
		if (reg->smax_value <= (s64)val)
			return 1;
		else if (reg->smin_value > (s64)val)
			return 0;
		break;
	}

	return -1;
}
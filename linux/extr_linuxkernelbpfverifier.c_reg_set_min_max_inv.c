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
struct bpf_reg_state {void* smax_value; void* smin_value; void* umax_value; void* umin_value; } ;

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
 int /*<<< orphan*/  __mark_reg_known (struct bpf_reg_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __reg_bound_offset (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  __reg_deduce_bounds (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  __update_reg_bounds (struct bpf_reg_state*) ; 
 void* max (void*,int /*<<< orphan*/ ) ; 
 void* max_t (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 void* min (void*,int /*<<< orphan*/ ) ; 
 void* min_t (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s64 ; 

__attribute__((used)) static void reg_set_min_max_inv(struct bpf_reg_state *true_reg,
				struct bpf_reg_state *false_reg, u64 val,
				u8 opcode)
{
	if (__is_pointer_value(false, false_reg))
		return;

	switch (opcode) {
	case BPF_JEQ:
		/* If this is false then we know nothing Jon Snow, but if it is
		 * true then we know for sure.
		 */
		__mark_reg_known(true_reg, val);
		break;
	case BPF_JNE:
		/* If this is true we know nothing Jon Snow, but if it is false
		 * we know the value for sure;
		 */
		__mark_reg_known(false_reg, val);
		break;
	case BPF_JGT:
		true_reg->umax_value = min(true_reg->umax_value, val - 1);
		false_reg->umin_value = max(false_reg->umin_value, val);
		break;
	case BPF_JSGT:
		true_reg->smax_value = min_t(s64, true_reg->smax_value, val - 1);
		false_reg->smin_value = max_t(s64, false_reg->smin_value, val);
		break;
	case BPF_JLT:
		true_reg->umin_value = max(true_reg->umin_value, val + 1);
		false_reg->umax_value = min(false_reg->umax_value, val);
		break;
	case BPF_JSLT:
		true_reg->smin_value = max_t(s64, true_reg->smin_value, val + 1);
		false_reg->smax_value = min_t(s64, false_reg->smax_value, val);
		break;
	case BPF_JGE:
		true_reg->umax_value = min(true_reg->umax_value, val);
		false_reg->umin_value = max(false_reg->umin_value, val + 1);
		break;
	case BPF_JSGE:
		true_reg->smax_value = min_t(s64, true_reg->smax_value, val);
		false_reg->smin_value = max_t(s64, false_reg->smin_value, val + 1);
		break;
	case BPF_JLE:
		true_reg->umin_value = max(true_reg->umin_value, val);
		false_reg->umax_value = min(false_reg->umax_value, val - 1);
		break;
	case BPF_JSLE:
		true_reg->smin_value = max_t(s64, true_reg->smin_value, val);
		false_reg->smax_value = min_t(s64, false_reg->smax_value, val - 1);
		break;
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
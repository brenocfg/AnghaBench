#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tn_buf ;
struct bpf_verifier_env {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
struct bpf_reg_state {int type; scalar_t__ smin_value; scalar_t__ umin_value; scalar_t__ smax_value; scalar_t__ umax_value; int /*<<< orphan*/  off; TYPE_4__ var_off; scalar_t__ precise; int /*<<< orphan*/  live; TYPE_1__* map_ptr; int /*<<< orphan*/  range; int /*<<< orphan*/  ref_obj_id; int /*<<< orphan*/  id; } ;
struct bpf_func_state {int allocated_stack; int acquired_refs; TYPE_3__* refs; TYPE_2__* stack; struct bpf_reg_state* regs; scalar_t__ frameno; } ;
typedef  enum bpf_reg_type { ____Placeholder_bpf_reg_type } bpf_reg_type ;
struct TYPE_9__ {int id; } ;
struct TYPE_8__ {size_t* slot_type; struct bpf_reg_state spilled_ptr; } ;
struct TYPE_7__ {int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; } ;

/* Variables and functions */
 int BPF_REG_SIZE ; 
 int CONST_PTR_TO_MAP ; 
 int MAX_BPF_REG ; 
 int NOT_INIT ; 
 int PTR_TO_MAP_VALUE ; 
 int PTR_TO_MAP_VALUE_OR_NULL ; 
 int PTR_TO_STACK ; 
 scalar_t__ S64_MAX ; 
 scalar_t__ S64_MIN ; 
 int SCALAR_VALUE ; 
 size_t STACK_INVALID ; 
 size_t STACK_SPILL ; 
 scalar_t__ U64_MAX ; 
 int /*<<< orphan*/  print_liveness (struct bpf_verifier_env*,int /*<<< orphan*/ ) ; 
 scalar_t__ reg_type_may_be_refcounted_or_null (int) ; 
 int /*<<< orphan*/ * reg_type_str ; 
 char* slot_type_char ; 
 scalar_t__ tnum_is_const (TYPE_4__) ; 
 int /*<<< orphan*/  tnum_is_unknown (TYPE_4__) ; 
 int /*<<< orphan*/  tnum_strn (char*,int,TYPE_4__) ; 
 scalar_t__ type_is_pkt_pointer (int) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static void print_verifier_state(struct bpf_verifier_env *env,
				 const struct bpf_func_state *state)
{
	const struct bpf_reg_state *reg;
	enum bpf_reg_type t;
	int i;

	if (state->frameno)
		verbose(env, " frame%d:", state->frameno);
	for (i = 0; i < MAX_BPF_REG; i++) {
		reg = &state->regs[i];
		t = reg->type;
		if (t == NOT_INIT)
			continue;
		verbose(env, " R%d", i);
		print_liveness(env, reg->live);
		verbose(env, "=%s", reg_type_str[t]);
		if (t == SCALAR_VALUE && reg->precise)
			verbose(env, "P");
		if ((t == SCALAR_VALUE || t == PTR_TO_STACK) &&
		    tnum_is_const(reg->var_off)) {
			/* reg->off should be 0 for SCALAR_VALUE */
			verbose(env, "%lld", reg->var_off.value + reg->off);
		} else {
			verbose(env, "(id=%d", reg->id);
			if (reg_type_may_be_refcounted_or_null(t))
				verbose(env, ",ref_obj_id=%d", reg->ref_obj_id);
			if (t != SCALAR_VALUE)
				verbose(env, ",off=%d", reg->off);
			if (type_is_pkt_pointer(t))
				verbose(env, ",r=%d", reg->range);
			else if (t == CONST_PTR_TO_MAP ||
				 t == PTR_TO_MAP_VALUE ||
				 t == PTR_TO_MAP_VALUE_OR_NULL)
				verbose(env, ",ks=%d,vs=%d",
					reg->map_ptr->key_size,
					reg->map_ptr->value_size);
			if (tnum_is_const(reg->var_off)) {
				/* Typically an immediate SCALAR_VALUE, but
				 * could be a pointer whose offset is too big
				 * for reg->off
				 */
				verbose(env, ",imm=%llx", reg->var_off.value);
			} else {
				if (reg->smin_value != reg->umin_value &&
				    reg->smin_value != S64_MIN)
					verbose(env, ",smin_value=%lld",
						(long long)reg->smin_value);
				if (reg->smax_value != reg->umax_value &&
				    reg->smax_value != S64_MAX)
					verbose(env, ",smax_value=%lld",
						(long long)reg->smax_value);
				if (reg->umin_value != 0)
					verbose(env, ",umin_value=%llu",
						(unsigned long long)reg->umin_value);
				if (reg->umax_value != U64_MAX)
					verbose(env, ",umax_value=%llu",
						(unsigned long long)reg->umax_value);
				if (!tnum_is_unknown(reg->var_off)) {
					char tn_buf[48];

					tnum_strn(tn_buf, sizeof(tn_buf), reg->var_off);
					verbose(env, ",var_off=%s", tn_buf);
				}
			}
			verbose(env, ")");
		}
	}
	for (i = 0; i < state->allocated_stack / BPF_REG_SIZE; i++) {
		char types_buf[BPF_REG_SIZE + 1];
		bool valid = false;
		int j;

		for (j = 0; j < BPF_REG_SIZE; j++) {
			if (state->stack[i].slot_type[j] != STACK_INVALID)
				valid = true;
			types_buf[j] = slot_type_char[
					state->stack[i].slot_type[j]];
		}
		types_buf[BPF_REG_SIZE] = 0;
		if (!valid)
			continue;
		verbose(env, " fp%d", (-i - 1) * BPF_REG_SIZE);
		print_liveness(env, state->stack[i].spilled_ptr.live);
		if (state->stack[i].slot_type[0] == STACK_SPILL) {
			reg = &state->stack[i].spilled_ptr;
			t = reg->type;
			verbose(env, "=%s", reg_type_str[t]);
			if (t == SCALAR_VALUE && reg->precise)
				verbose(env, "P");
			if (t == SCALAR_VALUE && tnum_is_const(reg->var_off))
				verbose(env, "%lld", reg->var_off.value + reg->off);
		} else {
			verbose(env, "=%s", types_buf);
		}
	}
	if (state->acquired_refs && state->refs[0].id) {
		verbose(env, " refs=%d", state->refs[0].id);
		for (i = 1; i < state->acquired_refs; i++)
			if (state->refs[i].id)
				verbose(env, ",%d", state->refs[i].id);
	}
	verbose(env, "\n");
}
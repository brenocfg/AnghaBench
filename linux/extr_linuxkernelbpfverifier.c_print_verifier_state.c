#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tn_buf ;
struct bpf_verifier_env {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
struct bpf_reg_state {int type; scalar_t__ smin_value; scalar_t__ umin_value; scalar_t__ smax_value; scalar_t__ umax_value; TYPE_4__ var_off; TYPE_1__* map_ptr; int /*<<< orphan*/  range; int /*<<< orphan*/  off; int /*<<< orphan*/  id; int /*<<< orphan*/  live; } ;
struct bpf_func_state {int allocated_stack; TYPE_3__* stack; struct bpf_reg_state* regs; scalar_t__ frameno; } ;
typedef  enum bpf_reg_type { ____Placeholder_bpf_reg_type } bpf_reg_type ;
struct TYPE_12__ {int /*<<< orphan*/  callsite; } ;
struct TYPE_9__ {size_t type; int /*<<< orphan*/  live; } ;
struct TYPE_10__ {scalar_t__* slot_type; TYPE_2__ spilled_ptr; } ;
struct TYPE_8__ {int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; } ;

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
 scalar_t__ STACK_SPILL ; 
 scalar_t__ STACK_ZERO ; 
 scalar_t__ U64_MAX ; 
 TYPE_7__* func (struct bpf_verifier_env*,struct bpf_reg_state const*) ; 
 int /*<<< orphan*/  print_liveness (struct bpf_verifier_env*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reg_type_str ; 
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
		if ((t == SCALAR_VALUE || t == PTR_TO_STACK) &&
		    tnum_is_const(reg->var_off)) {
			/* reg->off should be 0 for SCALAR_VALUE */
			verbose(env, "%lld", reg->var_off.value + reg->off);
			if (t == PTR_TO_STACK)
				verbose(env, ",call_%d", func(env, reg)->callsite);
		} else {
			verbose(env, "(id=%d", reg->id);
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
		if (state->stack[i].slot_type[0] == STACK_SPILL) {
			verbose(env, " fp%d",
				(-i - 1) * BPF_REG_SIZE);
			print_liveness(env, state->stack[i].spilled_ptr.live);
			verbose(env, "=%s",
				reg_type_str[state->stack[i].spilled_ptr.type]);
		}
		if (state->stack[i].slot_type[0] == STACK_ZERO)
			verbose(env, " fp%d=0", (-i - 1) * BPF_REG_SIZE);
	}
	verbose(env, "\n");
}
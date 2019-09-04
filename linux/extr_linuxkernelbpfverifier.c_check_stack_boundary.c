#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  tn_buf ;
struct bpf_verifier_env {TYPE_4__* cur_state; } ;
struct TYPE_6__ {int value; } ;
struct bpf_reg_state {size_t type; int off; TYPE_2__ var_off; } ;
struct bpf_func_state {int allocated_stack; int /*<<< orphan*/  frameno; TYPE_1__* stack; } ;
struct bpf_call_arg_meta {int access_size; int regno; scalar_t__ raw_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {scalar_t__* slot_type; } ;

/* Variables and functions */
 int BPF_REG_SIZE ; 
 int EACCES ; 
 int MAX_BPF_STACK ; 
 size_t PTR_TO_STACK ; 
 scalar_t__ STACK_MISC ; 
 scalar_t__ STACK_ZERO ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 struct bpf_func_state* func (struct bpf_verifier_env*,struct bpf_reg_state*) ; 
 int /*<<< orphan*/  mark_stack_slot_read (struct bpf_verifier_env*,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int* reg_type_str ; 
 scalar_t__ register_is_null (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  tnum_is_const (TYPE_2__) ; 
 int /*<<< orphan*/  tnum_strn (char*,int,TYPE_2__) ; 
 int update_stack_depth (struct bpf_verifier_env*,struct bpf_func_state*,int) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,int,...) ; 

__attribute__((used)) static int check_stack_boundary(struct bpf_verifier_env *env, int regno,
				int access_size, bool zero_size_allowed,
				struct bpf_call_arg_meta *meta)
{
	struct bpf_reg_state *reg = cur_regs(env) + regno;
	struct bpf_func_state *state = func(env, reg);
	int off, i, slot, spi;

	if (reg->type != PTR_TO_STACK) {
		/* Allow zero-byte read from NULL, regardless of pointer type */
		if (zero_size_allowed && access_size == 0 &&
		    register_is_null(reg))
			return 0;

		verbose(env, "R%d type=%s expected=%s\n", regno,
			reg_type_str[reg->type],
			reg_type_str[PTR_TO_STACK]);
		return -EACCES;
	}

	/* Only allow fixed-offset stack reads */
	if (!tnum_is_const(reg->var_off)) {
		char tn_buf[48];

		tnum_strn(tn_buf, sizeof(tn_buf), reg->var_off);
		verbose(env, "invalid variable stack read R%d var_off=%s\n",
			regno, tn_buf);
		return -EACCES;
	}
	off = reg->off + reg->var_off.value;
	if (off >= 0 || off < -MAX_BPF_STACK || off + access_size > 0 ||
	    access_size < 0 || (access_size == 0 && !zero_size_allowed)) {
		verbose(env, "invalid stack type R%d off=%d access_size=%d\n",
			regno, off, access_size);
		return -EACCES;
	}

	if (meta && meta->raw_mode) {
		meta->access_size = access_size;
		meta->regno = regno;
		return 0;
	}

	for (i = 0; i < access_size; i++) {
		u8 *stype;

		slot = -(off + i) - 1;
		spi = slot / BPF_REG_SIZE;
		if (state->allocated_stack <= slot)
			goto err;
		stype = &state->stack[spi].slot_type[slot % BPF_REG_SIZE];
		if (*stype == STACK_MISC)
			goto mark;
		if (*stype == STACK_ZERO) {
			/* helper can write anything into the stack */
			*stype = STACK_MISC;
			goto mark;
		}
err:
		verbose(env, "invalid indirect read from stack off %d+%d size %d\n",
			off, i, access_size);
		return -EACCES;
mark:
		/* reading any byte out of 8-byte 'spill_slot' will cause
		 * the whole slot to be marked as 'read'
		 */
		mark_stack_slot_read(env, env->cur_state, env->cur_state->parent,
				     spi, state->frameno);
	}
	return update_stack_depth(env, state, off);
}
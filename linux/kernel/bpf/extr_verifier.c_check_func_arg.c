#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {int type; scalar_t__ umax_value; scalar_t__ smin_value; scalar_t__ umin_value; int /*<<< orphan*/  var_off; int /*<<< orphan*/  smax_value; TYPE_1__* map_ptr; scalar_t__ ref_obj_id; } ;
struct bpf_call_arg_meta {scalar_t__ func_id; int raw_mode; scalar_t__ msize_umax_value; int /*<<< orphan*/  msize_smax_value; TYPE_1__* map_ptr; scalar_t__ ref_obj_id; } ;
typedef  enum bpf_reg_type { ____Placeholder_bpf_reg_type } bpf_reg_type ;
typedef  enum bpf_arg_type { ____Placeholder_bpf_arg_type } bpf_arg_type ;
struct TYPE_2__ {int key_size; int value_size; } ;

/* Variables and functions */
 int ARG_ANYTHING ; 
 int ARG_CONST_MAP_PTR ; 
 int ARG_CONST_SIZE ; 
 int ARG_CONST_SIZE_OR_ZERO ; 
 int ARG_DONTCARE ; 
 int ARG_PTR_TO_CTX ; 
 int ARG_PTR_TO_MAP_KEY ; 
 int ARG_PTR_TO_MAP_VALUE ; 
 int ARG_PTR_TO_MAP_VALUE_OR_NULL ; 
 int ARG_PTR_TO_MEM_OR_NULL ; 
 int ARG_PTR_TO_SOCKET ; 
 int ARG_PTR_TO_SOCK_COMMON ; 
 int ARG_PTR_TO_SPIN_LOCK ; 
 int ARG_PTR_TO_UNINIT_MAP_VALUE ; 
 int ARG_PTR_TO_UNINIT_MEM ; 
 scalar_t__ BPF_FUNC_spin_lock ; 
 scalar_t__ BPF_FUNC_spin_unlock ; 
 scalar_t__ BPF_MAX_VAR_SIZ ; 
 int /*<<< orphan*/  BPF_READ ; 
 int CONST_PTR_TO_MAP ; 
 int EACCES ; 
 int EFAULT ; 
 int PTR_TO_CTX ; 
 int PTR_TO_MAP_VALUE ; 
 int PTR_TO_SOCKET ; 
 int PTR_TO_SOCK_COMMON ; 
 int PTR_TO_STACK ; 
 int SCALAR_VALUE ; 
 int /*<<< orphan*/  SRC_OP ; 
 scalar_t__ arg_type_is_int_ptr (int) ; 
 scalar_t__ arg_type_is_mem_ptr (int) ; 
 scalar_t__ arg_type_is_mem_size (int) ; 
 int check_ctx_reg (struct bpf_verifier_env*,struct bpf_reg_state*,size_t) ; 
 int check_helper_mem_access (struct bpf_verifier_env*,size_t,int,int,struct bpf_call_arg_meta*) ; 
 int check_ptr_alignment (struct bpf_verifier_env*,struct bpf_reg_state*,int /*<<< orphan*/ ,int,int) ; 
 int check_reg_arg (struct bpf_verifier_env*,size_t,int /*<<< orphan*/ ) ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 int int_ptr_type_to_size (int) ; 
 scalar_t__ is_pointer_value (struct bpf_verifier_env*,size_t) ; 
 int mark_chain_precision (struct bpf_verifier_env*,size_t) ; 
 int /*<<< orphan*/  may_access_direct_pkt_data (struct bpf_verifier_env*,struct bpf_call_arg_meta*,int /*<<< orphan*/ ) ; 
 scalar_t__ process_spin_lock (struct bpf_verifier_env*,size_t,int) ; 
 scalar_t__* reg_type_str ; 
 scalar_t__ register_is_null (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  tnum_is_const (int /*<<< orphan*/ ) ; 
 scalar_t__ type_is_pkt_pointer (int) ; 
 int /*<<< orphan*/  type_is_sk_pointer (int) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int check_func_arg(struct bpf_verifier_env *env, u32 regno,
			  enum bpf_arg_type arg_type,
			  struct bpf_call_arg_meta *meta)
{
	struct bpf_reg_state *regs = cur_regs(env), *reg = &regs[regno];
	enum bpf_reg_type expected_type, type = reg->type;
	int err = 0;

	if (arg_type == ARG_DONTCARE)
		return 0;

	err = check_reg_arg(env, regno, SRC_OP);
	if (err)
		return err;

	if (arg_type == ARG_ANYTHING) {
		if (is_pointer_value(env, regno)) {
			verbose(env, "R%d leaks addr into helper function\n",
				regno);
			return -EACCES;
		}
		return 0;
	}

	if (type_is_pkt_pointer(type) &&
	    !may_access_direct_pkt_data(env, meta, BPF_READ)) {
		verbose(env, "helper access to the packet is not allowed\n");
		return -EACCES;
	}

	if (arg_type == ARG_PTR_TO_MAP_KEY ||
	    arg_type == ARG_PTR_TO_MAP_VALUE ||
	    arg_type == ARG_PTR_TO_UNINIT_MAP_VALUE ||
	    arg_type == ARG_PTR_TO_MAP_VALUE_OR_NULL) {
		expected_type = PTR_TO_STACK;
		if (register_is_null(reg) &&
		    arg_type == ARG_PTR_TO_MAP_VALUE_OR_NULL)
			/* final test in check_stack_boundary() */;
		else if (!type_is_pkt_pointer(type) &&
			 type != PTR_TO_MAP_VALUE &&
			 type != expected_type)
			goto err_type;
	} else if (arg_type == ARG_CONST_SIZE ||
		   arg_type == ARG_CONST_SIZE_OR_ZERO) {
		expected_type = SCALAR_VALUE;
		if (type != expected_type)
			goto err_type;
	} else if (arg_type == ARG_CONST_MAP_PTR) {
		expected_type = CONST_PTR_TO_MAP;
		if (type != expected_type)
			goto err_type;
	} else if (arg_type == ARG_PTR_TO_CTX) {
		expected_type = PTR_TO_CTX;
		if (type != expected_type)
			goto err_type;
		err = check_ctx_reg(env, reg, regno);
		if (err < 0)
			return err;
	} else if (arg_type == ARG_PTR_TO_SOCK_COMMON) {
		expected_type = PTR_TO_SOCK_COMMON;
		/* Any sk pointer can be ARG_PTR_TO_SOCK_COMMON */
		if (!type_is_sk_pointer(type))
			goto err_type;
		if (reg->ref_obj_id) {
			if (meta->ref_obj_id) {
				verbose(env, "verifier internal error: more than one arg with ref_obj_id R%d %u %u\n",
					regno, reg->ref_obj_id,
					meta->ref_obj_id);
				return -EFAULT;
			}
			meta->ref_obj_id = reg->ref_obj_id;
		}
	} else if (arg_type == ARG_PTR_TO_SOCKET) {
		expected_type = PTR_TO_SOCKET;
		if (type != expected_type)
			goto err_type;
	} else if (arg_type == ARG_PTR_TO_SPIN_LOCK) {
		if (meta->func_id == BPF_FUNC_spin_lock) {
			if (process_spin_lock(env, regno, true))
				return -EACCES;
		} else if (meta->func_id == BPF_FUNC_spin_unlock) {
			if (process_spin_lock(env, regno, false))
				return -EACCES;
		} else {
			verbose(env, "verifier internal error\n");
			return -EFAULT;
		}
	} else if (arg_type_is_mem_ptr(arg_type)) {
		expected_type = PTR_TO_STACK;
		/* One exception here. In case function allows for NULL to be
		 * passed in as argument, it's a SCALAR_VALUE type. Final test
		 * happens during stack boundary checking.
		 */
		if (register_is_null(reg) &&
		    arg_type == ARG_PTR_TO_MEM_OR_NULL)
			/* final test in check_stack_boundary() */;
		else if (!type_is_pkt_pointer(type) &&
			 type != PTR_TO_MAP_VALUE &&
			 type != expected_type)
			goto err_type;
		meta->raw_mode = arg_type == ARG_PTR_TO_UNINIT_MEM;
	} else if (arg_type_is_int_ptr(arg_type)) {
		expected_type = PTR_TO_STACK;
		if (!type_is_pkt_pointer(type) &&
		    type != PTR_TO_MAP_VALUE &&
		    type != expected_type)
			goto err_type;
	} else {
		verbose(env, "unsupported arg_type %d\n", arg_type);
		return -EFAULT;
	}

	if (arg_type == ARG_CONST_MAP_PTR) {
		/* bpf_map_xxx(map_ptr) call: remember that map_ptr */
		meta->map_ptr = reg->map_ptr;
	} else if (arg_type == ARG_PTR_TO_MAP_KEY) {
		/* bpf_map_xxx(..., map_ptr, ..., key) call:
		 * check that [key, key + map->key_size) are within
		 * stack limits and initialized
		 */
		if (!meta->map_ptr) {
			/* in function declaration map_ptr must come before
			 * map_key, so that it's verified and known before
			 * we have to check map_key here. Otherwise it means
			 * that kernel subsystem misconfigured verifier
			 */
			verbose(env, "invalid map_ptr to access map->key\n");
			return -EACCES;
		}
		err = check_helper_mem_access(env, regno,
					      meta->map_ptr->key_size, false,
					      NULL);
	} else if (arg_type == ARG_PTR_TO_MAP_VALUE ||
		   (arg_type == ARG_PTR_TO_MAP_VALUE_OR_NULL &&
		    !register_is_null(reg)) ||
		   arg_type == ARG_PTR_TO_UNINIT_MAP_VALUE) {
		/* bpf_map_xxx(..., map_ptr, ..., value) call:
		 * check [value, value + map->value_size) validity
		 */
		if (!meta->map_ptr) {
			/* kernel subsystem misconfigured verifier */
			verbose(env, "invalid map_ptr to access map->value\n");
			return -EACCES;
		}
		meta->raw_mode = (arg_type == ARG_PTR_TO_UNINIT_MAP_VALUE);
		err = check_helper_mem_access(env, regno,
					      meta->map_ptr->value_size, false,
					      meta);
	} else if (arg_type_is_mem_size(arg_type)) {
		bool zero_size_allowed = (arg_type == ARG_CONST_SIZE_OR_ZERO);

		/* remember the mem_size which may be used later
		 * to refine return values.
		 */
		meta->msize_smax_value = reg->smax_value;
		meta->msize_umax_value = reg->umax_value;

		/* The register is SCALAR_VALUE; the access check
		 * happens using its boundaries.
		 */
		if (!tnum_is_const(reg->var_off))
			/* For unprivileged variable accesses, disable raw
			 * mode so that the program is required to
			 * initialize all the memory that the helper could
			 * just partially fill up.
			 */
			meta = NULL;

		if (reg->smin_value < 0) {
			verbose(env, "R%d min value is negative, either use unsigned or 'var &= const'\n",
				regno);
			return -EACCES;
		}

		if (reg->umin_value == 0) {
			err = check_helper_mem_access(env, regno - 1, 0,
						      zero_size_allowed,
						      meta);
			if (err)
				return err;
		}

		if (reg->umax_value >= BPF_MAX_VAR_SIZ) {
			verbose(env, "R%d unbounded memory access, use 'var &= const' or 'if (var < const)'\n",
				regno);
			return -EACCES;
		}
		err = check_helper_mem_access(env, regno - 1,
					      reg->umax_value,
					      zero_size_allowed, meta);
		if (!err)
			err = mark_chain_precision(env, regno);
	} else if (arg_type_is_int_ptr(arg_type)) {
		int size = int_ptr_type_to_size(arg_type);

		err = check_helper_mem_access(env, regno, size, false, meta);
		if (err)
			return err;
		err = check_ptr_alignment(env, reg, 0, size, true);
	}

	return err;
err_type:
	verbose(env, "R%d type=%s expected=%s\n", regno,
		reg_type_str[type], reg_type_str[expected_type]);
	return -EACCES;
}
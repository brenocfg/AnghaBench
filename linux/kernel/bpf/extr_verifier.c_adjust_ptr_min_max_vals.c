#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct bpf_verifier_state {size_t curframe; struct bpf_func_state** frame; } ;
struct bpf_verifier_env {int /*<<< orphan*/  allow_ptr_leaks; int /*<<< orphan*/  id_gen; struct bpf_verifier_state* cur_state; } ;
struct TYPE_8__ {scalar_t__ value; } ;
typedef  struct bpf_reg_state {scalar_t__ smin_value; scalar_t__ smax_value; scalar_t__ umin_value; scalar_t__ umax_value; int type; scalar_t__ off; TYPE_1__ var_off; int /*<<< orphan*/  raw; int /*<<< orphan*/  id; } const bpf_reg_state ;
struct bpf_insn {size_t dst_reg; size_t src_reg; int /*<<< orphan*/  code; } ;
struct bpf_func_state {struct bpf_reg_state const* regs; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  BPF_ADD 143 
 scalar_t__ BPF_ALU64 ; 
#define  BPF_AND 142 
 scalar_t__ BPF_CLASS (int /*<<< orphan*/ ) ; 
 int BPF_OP (int /*<<< orphan*/ ) ; 
#define  BPF_OR 141 
#define  BPF_SUB 140 
#define  BPF_XOR 139 
#define  CONST_PTR_TO_MAP 138 
 int EACCES ; 
 int EINVAL ; 
#define  PTR_TO_MAP_VALUE 137 
#define  PTR_TO_MAP_VALUE_OR_NULL 136 
#define  PTR_TO_PACKET_END 135 
#define  PTR_TO_SOCKET 134 
#define  PTR_TO_SOCKET_OR_NULL 133 
#define  PTR_TO_SOCK_COMMON 132 
#define  PTR_TO_SOCK_COMMON_OR_NULL 131 
 size_t PTR_TO_STACK ; 
#define  PTR_TO_TCP_SOCK 130 
#define  PTR_TO_TCP_SOCK_OR_NULL 129 
#define  PTR_TO_XDP_SOCK 128 
 void* S64_MAX ; 
 void* S64_MIN ; 
 void* U64_MAX ; 
 int /*<<< orphan*/  __mark_reg_unknown (struct bpf_reg_state const*) ; 
 int /*<<< orphan*/  __reg_bound_offset (struct bpf_reg_state const*) ; 
 int /*<<< orphan*/  __reg_deduce_bounds (struct bpf_reg_state const*) ; 
 int /*<<< orphan*/  __update_reg_bounds (struct bpf_reg_state const*) ; 
 int /*<<< orphan*/ * bpf_alu_string ; 
 scalar_t__ check_map_access (struct bpf_verifier_env*,size_t,scalar_t__,int,int) ; 
 int /*<<< orphan*/  check_reg_sane_offset (struct bpf_verifier_env*,struct bpf_reg_state const*,size_t) ; 
 scalar_t__ check_stack_access (struct bpf_verifier_env*,struct bpf_reg_state const*,scalar_t__,int) ; 
 int /*<<< orphan*/  reg_is_pkt_pointer (struct bpf_reg_state const*) ; 
 int /*<<< orphan*/ * reg_type_str ; 
 int sanitize_ptr_alu (struct bpf_verifier_env*,struct bpf_insn*,struct bpf_reg_state const*,struct bpf_reg_state const*,int) ; 
 int /*<<< orphan*/  signed_add_overflows (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  signed_sub_overflows (scalar_t__,scalar_t__) ; 
 TYPE_1__ tnum_add (TYPE_1__,TYPE_1__) ; 
 int tnum_is_const (TYPE_1__) ; 
 TYPE_1__ tnum_sub (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,size_t,...) ; 

__attribute__((used)) static int adjust_ptr_min_max_vals(struct bpf_verifier_env *env,
				   struct bpf_insn *insn,
				   const struct bpf_reg_state *ptr_reg,
				   const struct bpf_reg_state *off_reg)
{
	struct bpf_verifier_state *vstate = env->cur_state;
	struct bpf_func_state *state = vstate->frame[vstate->curframe];
	struct bpf_reg_state *regs = state->regs, *dst_reg;
	bool known = tnum_is_const(off_reg->var_off);
	s64 smin_val = off_reg->smin_value, smax_val = off_reg->smax_value,
	    smin_ptr = ptr_reg->smin_value, smax_ptr = ptr_reg->smax_value;
	u64 umin_val = off_reg->umin_value, umax_val = off_reg->umax_value,
	    umin_ptr = ptr_reg->umin_value, umax_ptr = ptr_reg->umax_value;
	u32 dst = insn->dst_reg, src = insn->src_reg;
	u8 opcode = BPF_OP(insn->code);
	int ret;

	dst_reg = &regs[dst];

	if ((known && (smin_val != smax_val || umin_val != umax_val)) ||
	    smin_val > smax_val || umin_val > umax_val) {
		/* Taint dst register if offset had invalid bounds derived from
		 * e.g. dead branches.
		 */
		__mark_reg_unknown(dst_reg);
		return 0;
	}

	if (BPF_CLASS(insn->code) != BPF_ALU64) {
		/* 32-bit ALU ops on pointers produce (meaningless) scalars */
		verbose(env,
			"R%d 32-bit pointer arithmetic prohibited\n",
			dst);
		return -EACCES;
	}

	switch (ptr_reg->type) {
	case PTR_TO_MAP_VALUE_OR_NULL:
		verbose(env, "R%d pointer arithmetic on %s prohibited, null-check it first\n",
			dst, reg_type_str[ptr_reg->type]);
		return -EACCES;
	case CONST_PTR_TO_MAP:
	case PTR_TO_PACKET_END:
	case PTR_TO_SOCKET:
	case PTR_TO_SOCKET_OR_NULL:
	case PTR_TO_SOCK_COMMON:
	case PTR_TO_SOCK_COMMON_OR_NULL:
	case PTR_TO_TCP_SOCK:
	case PTR_TO_TCP_SOCK_OR_NULL:
	case PTR_TO_XDP_SOCK:
		verbose(env, "R%d pointer arithmetic on %s prohibited\n",
			dst, reg_type_str[ptr_reg->type]);
		return -EACCES;
	case PTR_TO_MAP_VALUE:
		if (!env->allow_ptr_leaks && !known && (smin_val < 0) != (smax_val < 0)) {
			verbose(env, "R%d has unknown scalar with mixed signed bounds, pointer arithmetic with it prohibited for !root\n",
				off_reg == dst_reg ? dst : src);
			return -EACCES;
		}
		/* fall-through */
	default:
		break;
	}

	/* In case of 'scalar += pointer', dst_reg inherits pointer type and id.
	 * The id may be overwritten later if we create a new variable offset.
	 */
	dst_reg->type = ptr_reg->type;
	dst_reg->id = ptr_reg->id;

	if (!check_reg_sane_offset(env, off_reg, ptr_reg->type) ||
	    !check_reg_sane_offset(env, ptr_reg, ptr_reg->type))
		return -EINVAL;

	switch (opcode) {
	case BPF_ADD:
		ret = sanitize_ptr_alu(env, insn, ptr_reg, dst_reg, smin_val < 0);
		if (ret < 0) {
			verbose(env, "R%d tried to add from different maps or paths\n", dst);
			return ret;
		}
		/* We can take a fixed offset as long as it doesn't overflow
		 * the s32 'off' field
		 */
		if (known && (ptr_reg->off + smin_val ==
			      (s64)(s32)(ptr_reg->off + smin_val))) {
			/* pointer += K.  Accumulate it into fixed offset */
			dst_reg->smin_value = smin_ptr;
			dst_reg->smax_value = smax_ptr;
			dst_reg->umin_value = umin_ptr;
			dst_reg->umax_value = umax_ptr;
			dst_reg->var_off = ptr_reg->var_off;
			dst_reg->off = ptr_reg->off + smin_val;
			dst_reg->raw = ptr_reg->raw;
			break;
		}
		/* A new variable offset is created.  Note that off_reg->off
		 * == 0, since it's a scalar.
		 * dst_reg gets the pointer type and since some positive
		 * integer value was added to the pointer, give it a new 'id'
		 * if it's a PTR_TO_PACKET.
		 * this creates a new 'base' pointer, off_reg (variable) gets
		 * added into the variable offset, and we copy the fixed offset
		 * from ptr_reg.
		 */
		if (signed_add_overflows(smin_ptr, smin_val) ||
		    signed_add_overflows(smax_ptr, smax_val)) {
			dst_reg->smin_value = S64_MIN;
			dst_reg->smax_value = S64_MAX;
		} else {
			dst_reg->smin_value = smin_ptr + smin_val;
			dst_reg->smax_value = smax_ptr + smax_val;
		}
		if (umin_ptr + umin_val < umin_ptr ||
		    umax_ptr + umax_val < umax_ptr) {
			dst_reg->umin_value = 0;
			dst_reg->umax_value = U64_MAX;
		} else {
			dst_reg->umin_value = umin_ptr + umin_val;
			dst_reg->umax_value = umax_ptr + umax_val;
		}
		dst_reg->var_off = tnum_add(ptr_reg->var_off, off_reg->var_off);
		dst_reg->off = ptr_reg->off;
		dst_reg->raw = ptr_reg->raw;
		if (reg_is_pkt_pointer(ptr_reg)) {
			dst_reg->id = ++env->id_gen;
			/* something was added to pkt_ptr, set range to zero */
			dst_reg->raw = 0;
		}
		break;
	case BPF_SUB:
		ret = sanitize_ptr_alu(env, insn, ptr_reg, dst_reg, smin_val < 0);
		if (ret < 0) {
			verbose(env, "R%d tried to sub from different maps or paths\n", dst);
			return ret;
		}
		if (dst_reg == off_reg) {
			/* scalar -= pointer.  Creates an unknown scalar */
			verbose(env, "R%d tried to subtract pointer from scalar\n",
				dst);
			return -EACCES;
		}
		/* We don't allow subtraction from FP, because (according to
		 * test_verifier.c test "invalid fp arithmetic", JITs might not
		 * be able to deal with it.
		 */
		if (ptr_reg->type == PTR_TO_STACK) {
			verbose(env, "R%d subtraction from stack pointer prohibited\n",
				dst);
			return -EACCES;
		}
		if (known && (ptr_reg->off - smin_val ==
			      (s64)(s32)(ptr_reg->off - smin_val))) {
			/* pointer -= K.  Subtract it from fixed offset */
			dst_reg->smin_value = smin_ptr;
			dst_reg->smax_value = smax_ptr;
			dst_reg->umin_value = umin_ptr;
			dst_reg->umax_value = umax_ptr;
			dst_reg->var_off = ptr_reg->var_off;
			dst_reg->id = ptr_reg->id;
			dst_reg->off = ptr_reg->off - smin_val;
			dst_reg->raw = ptr_reg->raw;
			break;
		}
		/* A new variable offset is created.  If the subtrahend is known
		 * nonnegative, then any reg->range we had before is still good.
		 */
		if (signed_sub_overflows(smin_ptr, smax_val) ||
		    signed_sub_overflows(smax_ptr, smin_val)) {
			/* Overflow possible, we know nothing */
			dst_reg->smin_value = S64_MIN;
			dst_reg->smax_value = S64_MAX;
		} else {
			dst_reg->smin_value = smin_ptr - smax_val;
			dst_reg->smax_value = smax_ptr - smin_val;
		}
		if (umin_ptr < umax_val) {
			/* Overflow possible, we know nothing */
			dst_reg->umin_value = 0;
			dst_reg->umax_value = U64_MAX;
		} else {
			/* Cannot overflow (as long as bounds are consistent) */
			dst_reg->umin_value = umin_ptr - umax_val;
			dst_reg->umax_value = umax_ptr - umin_val;
		}
		dst_reg->var_off = tnum_sub(ptr_reg->var_off, off_reg->var_off);
		dst_reg->off = ptr_reg->off;
		dst_reg->raw = ptr_reg->raw;
		if (reg_is_pkt_pointer(ptr_reg)) {
			dst_reg->id = ++env->id_gen;
			/* something was added to pkt_ptr, set range to zero */
			if (smin_val < 0)
				dst_reg->raw = 0;
		}
		break;
	case BPF_AND:
	case BPF_OR:
	case BPF_XOR:
		/* bitwise ops on pointers are troublesome, prohibit. */
		verbose(env, "R%d bitwise operator %s on pointer prohibited\n",
			dst, bpf_alu_string[opcode >> 4]);
		return -EACCES;
	default:
		/* other operators (e.g. MUL,LSH) produce non-pointer results */
		verbose(env, "R%d pointer arithmetic with %s operator prohibited\n",
			dst, bpf_alu_string[opcode >> 4]);
		return -EACCES;
	}

	if (!check_reg_sane_offset(env, dst_reg, ptr_reg->type))
		return -EINVAL;

	__update_reg_bounds(dst_reg);
	__reg_deduce_bounds(dst_reg);
	__reg_bound_offset(dst_reg);

	/* For unprivileged we require that resulting offset must be in bounds
	 * in order to be able to sanitize access later on.
	 */
	if (!env->allow_ptr_leaks) {
		if (dst_reg->type == PTR_TO_MAP_VALUE &&
		    check_map_access(env, dst, dst_reg->off, 1, false)) {
			verbose(env, "R%d pointer arithmetic of map value goes out of range, "
				"prohibited for !root\n", dst);
			return -EACCES;
		} else if (dst_reg->type == PTR_TO_STACK &&
			   check_stack_access(env, dst_reg, dst_reg->off +
					      dst_reg->var_off.value, 1)) {
			verbose(env, "R%d stack pointer arithmetic goes out of range, "
				"prohibited for !root\n", dst);
			return -EACCES;
		}
	}

	return 0;
}
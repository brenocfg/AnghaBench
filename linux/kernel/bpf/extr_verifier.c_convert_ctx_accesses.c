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
typedef  unsigned long long u8 ;
typedef  int u32 ;
struct bpf_verifier_ops {int (* gen_prologue ) (struct bpf_insn*,scalar_t__,struct bpf_prog*) ;int (* convert_ctx_access ) (int,struct bpf_insn*,struct bpf_insn*,struct bpf_prog*,int*) ;} ;
struct bpf_verifier_env {struct bpf_prog* prog; TYPE_1__* insn_aux_data; scalar_t__ seen_direct_write; struct bpf_verifier_ops* ops; } ;
struct bpf_prog {int len; struct bpf_insn* insnsi; int /*<<< orphan*/  aux; } ;
struct bpf_insn {unsigned long long code; int off; int /*<<< orphan*/  dst_reg; } ;
typedef  enum bpf_access_type { ____Placeholder_bpf_access_type } bpf_access_type ;
typedef  int (* bpf_convert_ctx_access_t ) (int,struct bpf_insn*,struct bpf_insn*,struct bpf_prog*,int*) ;
struct TYPE_2__ {int ptr_type; int ctx_field_size; scalar_t__ sanitize_stack_off; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bpf_insn*) ; 
 struct bpf_insn BPF_ALU32_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_ALU64_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  BPF_AND ; 
 unsigned long long BPF_B ; 
 unsigned long long BPF_DW ; 
 unsigned long long BPF_H ; 
 int BPF_LDST_BYTES (struct bpf_insn*) ; 
 unsigned long long BPF_LDX ; 
 unsigned long long BPF_MEM ; 
 int BPF_READ ; 
 int /*<<< orphan*/  BPF_REG_FP ; 
 int /*<<< orphan*/  BPF_RSH ; 
 unsigned long long BPF_STX ; 
 struct bpf_insn BPF_ST_MEM (unsigned long long,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long long BPF_W ; 
 int BPF_WRITE ; 
 int EINVAL ; 
 int ENOMEM ; 
#define  PTR_TO_CTX 132 
#define  PTR_TO_SOCKET 131 
#define  PTR_TO_SOCK_COMMON 130 
#define  PTR_TO_TCP_SOCK 129 
#define  PTR_TO_XDP_SOCK 128 
 int bpf_ctx_narrow_access_offset (int,int,int) ; 
 int bpf_ctx_off_adjust_machine (int) ; 
 struct bpf_prog* bpf_patch_insn_data (struct bpf_verifier_env*,int,struct bpf_insn*,int) ; 
 scalar_t__ bpf_prog_is_dev_bound (int /*<<< orphan*/ ) ; 
 int bpf_sock_convert_ctx_access (int,struct bpf_insn*,struct bpf_insn*,struct bpf_prog*,int*) ; 
 int bpf_tcp_sock_convert_ctx_access (int,struct bpf_insn*,struct bpf_insn*,struct bpf_prog*,int*) ; 
 int bpf_xdp_sock_convert_ctx_access (int,struct bpf_insn*,struct bpf_insn*,struct bpf_prog*,int*) ; 
 int stub1 (struct bpf_insn*,scalar_t__,struct bpf_prog*) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*) ; 

__attribute__((used)) static int convert_ctx_accesses(struct bpf_verifier_env *env)
{
	const struct bpf_verifier_ops *ops = env->ops;
	int i, cnt, size, ctx_field_size, delta = 0;
	const int insn_cnt = env->prog->len;
	struct bpf_insn insn_buf[16], *insn;
	u32 target_size, size_default, off;
	struct bpf_prog *new_prog;
	enum bpf_access_type type;
	bool is_narrower_load;

	if (ops->gen_prologue || env->seen_direct_write) {
		if (!ops->gen_prologue) {
			verbose(env, "bpf verifier is misconfigured\n");
			return -EINVAL;
		}
		cnt = ops->gen_prologue(insn_buf, env->seen_direct_write,
					env->prog);
		if (cnt >= ARRAY_SIZE(insn_buf)) {
			verbose(env, "bpf verifier is misconfigured\n");
			return -EINVAL;
		} else if (cnt) {
			new_prog = bpf_patch_insn_data(env, 0, insn_buf, cnt);
			if (!new_prog)
				return -ENOMEM;

			env->prog = new_prog;
			delta += cnt - 1;
		}
	}

	if (bpf_prog_is_dev_bound(env->prog->aux))
		return 0;

	insn = env->prog->insnsi + delta;

	for (i = 0; i < insn_cnt; i++, insn++) {
		bpf_convert_ctx_access_t convert_ctx_access;

		if (insn->code == (BPF_LDX | BPF_MEM | BPF_B) ||
		    insn->code == (BPF_LDX | BPF_MEM | BPF_H) ||
		    insn->code == (BPF_LDX | BPF_MEM | BPF_W) ||
		    insn->code == (BPF_LDX | BPF_MEM | BPF_DW))
			type = BPF_READ;
		else if (insn->code == (BPF_STX | BPF_MEM | BPF_B) ||
			 insn->code == (BPF_STX | BPF_MEM | BPF_H) ||
			 insn->code == (BPF_STX | BPF_MEM | BPF_W) ||
			 insn->code == (BPF_STX | BPF_MEM | BPF_DW))
			type = BPF_WRITE;
		else
			continue;

		if (type == BPF_WRITE &&
		    env->insn_aux_data[i + delta].sanitize_stack_off) {
			struct bpf_insn patch[] = {
				/* Sanitize suspicious stack slot with zero.
				 * There are no memory dependencies for this store,
				 * since it's only using frame pointer and immediate
				 * constant of zero
				 */
				BPF_ST_MEM(BPF_DW, BPF_REG_FP,
					   env->insn_aux_data[i + delta].sanitize_stack_off,
					   0),
				/* the original STX instruction will immediately
				 * overwrite the same stack slot with appropriate value
				 */
				*insn,
			};

			cnt = ARRAY_SIZE(patch);
			new_prog = bpf_patch_insn_data(env, i + delta, patch, cnt);
			if (!new_prog)
				return -ENOMEM;

			delta    += cnt - 1;
			env->prog = new_prog;
			insn      = new_prog->insnsi + i + delta;
			continue;
		}

		switch (env->insn_aux_data[i + delta].ptr_type) {
		case PTR_TO_CTX:
			if (!ops->convert_ctx_access)
				continue;
			convert_ctx_access = ops->convert_ctx_access;
			break;
		case PTR_TO_SOCKET:
		case PTR_TO_SOCK_COMMON:
			convert_ctx_access = bpf_sock_convert_ctx_access;
			break;
		case PTR_TO_TCP_SOCK:
			convert_ctx_access = bpf_tcp_sock_convert_ctx_access;
			break;
		case PTR_TO_XDP_SOCK:
			convert_ctx_access = bpf_xdp_sock_convert_ctx_access;
			break;
		default:
			continue;
		}

		ctx_field_size = env->insn_aux_data[i + delta].ctx_field_size;
		size = BPF_LDST_BYTES(insn);

		/* If the read access is a narrower load of the field,
		 * convert to a 4/8-byte load, to minimum program type specific
		 * convert_ctx_access changes. If conversion is successful,
		 * we will apply proper mask to the result.
		 */
		is_narrower_load = size < ctx_field_size;
		size_default = bpf_ctx_off_adjust_machine(ctx_field_size);
		off = insn->off;
		if (is_narrower_load) {
			u8 size_code;

			if (type == BPF_WRITE) {
				verbose(env, "bpf verifier narrow ctx access misconfigured\n");
				return -EINVAL;
			}

			size_code = BPF_H;
			if (ctx_field_size == 4)
				size_code = BPF_W;
			else if (ctx_field_size == 8)
				size_code = BPF_DW;

			insn->off = off & ~(size_default - 1);
			insn->code = BPF_LDX | BPF_MEM | size_code;
		}

		target_size = 0;
		cnt = convert_ctx_access(type, insn, insn_buf, env->prog,
					 &target_size);
		if (cnt == 0 || cnt >= ARRAY_SIZE(insn_buf) ||
		    (ctx_field_size && !target_size)) {
			verbose(env, "bpf verifier is misconfigured\n");
			return -EINVAL;
		}

		if (is_narrower_load && size < target_size) {
			u8 shift = bpf_ctx_narrow_access_offset(
				off, size, size_default) * 8;
			if (ctx_field_size <= 4) {
				if (shift)
					insn_buf[cnt++] = BPF_ALU32_IMM(BPF_RSH,
									insn->dst_reg,
									shift);
				insn_buf[cnt++] = BPF_ALU32_IMM(BPF_AND, insn->dst_reg,
								(1 << size * 8) - 1);
			} else {
				if (shift)
					insn_buf[cnt++] = BPF_ALU64_IMM(BPF_RSH,
									insn->dst_reg,
									shift);
				insn_buf[cnt++] = BPF_ALU64_IMM(BPF_AND, insn->dst_reg,
								(1ULL << size * 8) - 1);
			}
		}

		new_prog = bpf_patch_insn_data(env, i + delta, insn_buf, cnt);
		if (!new_prog)
			return -ENOMEM;

		delta += cnt - 1;

		/* keep walking new program and skip insns we just inserted */
		env->prog = new_prog;
		insn      = new_prog->insnsi + i + delta;
	}

	return 0;
}
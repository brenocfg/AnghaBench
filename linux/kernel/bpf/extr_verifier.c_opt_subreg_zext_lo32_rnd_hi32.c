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
union bpf_attr {int prog_flags; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bpf_verifier_env {struct bpf_insn_aux_data* insn_aux_data; struct bpf_prog* prog; } ;
struct bpf_prog {int len; struct bpf_insn* insnsi; } ;
struct bpf_insn_aux_data {scalar_t__ ptr_type; int /*<<< orphan*/  zext_dst; } ;
struct bpf_insn {scalar_t__ code; int /*<<< orphan*/  dst_reg; int /*<<< orphan*/  src_reg; int /*<<< orphan*/  imm; } ;

/* Variables and functions */
 struct bpf_insn BPF_ALU64_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bpf_insn BPF_ALU64_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_CLASS (scalar_t__) ; 
 int BPF_F_TEST_RND_HI32 ; 
 scalar_t__ BPF_IMM ; 
 scalar_t__ BPF_LD ; 
 scalar_t__ BPF_LDX ; 
 int /*<<< orphan*/  BPF_LSH ; 
 scalar_t__ BPF_MODE (scalar_t__) ; 
 int /*<<< orphan*/  BPF_MOV ; 
 int /*<<< orphan*/  BPF_OR ; 
 int /*<<< orphan*/  BPF_REG_AX ; 
 struct bpf_insn BPF_ZEXT_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DST_OP ; 
 int ENOMEM ; 
 scalar_t__ PTR_TO_CTX ; 
 int /*<<< orphan*/  bpf_jit_needs_zext () ; 
 struct bpf_prog* bpf_patch_insn_data (struct bpf_verifier_env*,int,struct bpf_insn*,int) ; 
 int /*<<< orphan*/  get_random_int () ; 
 scalar_t__ insn_no_def (struct bpf_insn*) ; 
 scalar_t__ is_reg64 (struct bpf_verifier_env*,struct bpf_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opt_subreg_zext_lo32_rnd_hi32(struct bpf_verifier_env *env,
					 const union bpf_attr *attr)
{
	struct bpf_insn *patch, zext_patch[2], rnd_hi32_patch[4];
	struct bpf_insn_aux_data *aux = env->insn_aux_data;
	int i, patch_len, delta = 0, len = env->prog->len;
	struct bpf_insn *insns = env->prog->insnsi;
	struct bpf_prog *new_prog;
	bool rnd_hi32;

	rnd_hi32 = attr->prog_flags & BPF_F_TEST_RND_HI32;
	zext_patch[1] = BPF_ZEXT_REG(0);
	rnd_hi32_patch[1] = BPF_ALU64_IMM(BPF_MOV, BPF_REG_AX, 0);
	rnd_hi32_patch[2] = BPF_ALU64_IMM(BPF_LSH, BPF_REG_AX, 32);
	rnd_hi32_patch[3] = BPF_ALU64_REG(BPF_OR, 0, BPF_REG_AX);
	for (i = 0; i < len; i++) {
		int adj_idx = i + delta;
		struct bpf_insn insn;

		insn = insns[adj_idx];
		if (!aux[adj_idx].zext_dst) {
			u8 code, class;
			u32 imm_rnd;

			if (!rnd_hi32)
				continue;

			code = insn.code;
			class = BPF_CLASS(code);
			if (insn_no_def(&insn))
				continue;

			/* NOTE: arg "reg" (the fourth one) is only used for
			 *       BPF_STX which has been ruled out in above
			 *       check, it is safe to pass NULL here.
			 */
			if (is_reg64(env, &insn, insn.dst_reg, NULL, DST_OP)) {
				if (class == BPF_LD &&
				    BPF_MODE(code) == BPF_IMM)
					i++;
				continue;
			}

			/* ctx load could be transformed into wider load. */
			if (class == BPF_LDX &&
			    aux[adj_idx].ptr_type == PTR_TO_CTX)
				continue;

			imm_rnd = get_random_int();
			rnd_hi32_patch[0] = insn;
			rnd_hi32_patch[1].imm = imm_rnd;
			rnd_hi32_patch[3].dst_reg = insn.dst_reg;
			patch = rnd_hi32_patch;
			patch_len = 4;
			goto apply_patch_buffer;
		}

		if (!bpf_jit_needs_zext())
			continue;

		zext_patch[0] = insn;
		zext_patch[1].dst_reg = insn.dst_reg;
		zext_patch[1].src_reg = insn.dst_reg;
		patch = zext_patch;
		patch_len = 2;
apply_patch_buffer:
		new_prog = bpf_patch_insn_data(env, adj_idx, patch, patch_len);
		if (!new_prog)
			return -ENOMEM;
		env->prog = new_prog;
		insns = new_prog->insnsi;
		aux = env->insn_aux_data;
		delta += patch_len - 1;
	}

	return 0;
}
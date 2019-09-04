#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct fd {int dummy; } ;
struct bpf_verifier_env {int used_map_cnt; TYPE_1__* prog; struct bpf_map** used_maps; } ;
struct bpf_map {scalar_t__ map_type; } ;
struct bpf_insn {int code; scalar_t__ imm; scalar_t__ dst_reg; scalar_t__ src_reg; scalar_t__ off; } ;
struct TYPE_4__ {int len; struct bpf_insn* insnsi; } ;

/* Variables and functions */
 scalar_t__ BPF_CLASS (int) ; 
 int BPF_DW ; 
 int BPF_IMM ; 
 int BPF_LD ; 
 scalar_t__ BPF_LDX ; 
 scalar_t__ BPF_MAP_TYPE_CGROUP_STORAGE ; 
 scalar_t__ BPF_MEM ; 
 scalar_t__ BPF_MODE (int) ; 
 scalar_t__ BPF_PSEUDO_MAP_FD ; 
 scalar_t__ BPF_STX ; 
 scalar_t__ BPF_XADD ; 
 int E2BIG ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct bpf_map*) ; 
 scalar_t__ MAX_USED_MAPS ; 
 int PTR_ERR (struct bpf_map*) ; 
 struct bpf_map* __bpf_map_get (struct fd) ; 
 scalar_t__ bpf_cgroup_storage_assign (TYPE_1__*,struct bpf_map*) ; 
 struct bpf_map* bpf_map_inc (struct bpf_map*,int) ; 
 int /*<<< orphan*/  bpf_opcode_in_insntable (int) ; 
 int bpf_prog_calc_tag (TYPE_1__*) ; 
 int check_map_prog_compatibility (struct bpf_verifier_env*,struct bpf_map*,TYPE_1__*) ; 
 struct fd fdget (scalar_t__) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int replace_map_fd_with_map_ptr(struct bpf_verifier_env *env)
{
	struct bpf_insn *insn = env->prog->insnsi;
	int insn_cnt = env->prog->len;
	int i, j, err;

	err = bpf_prog_calc_tag(env->prog);
	if (err)
		return err;

	for (i = 0; i < insn_cnt; i++, insn++) {
		if (BPF_CLASS(insn->code) == BPF_LDX &&
		    (BPF_MODE(insn->code) != BPF_MEM || insn->imm != 0)) {
			verbose(env, "BPF_LDX uses reserved fields\n");
			return -EINVAL;
		}

		if (BPF_CLASS(insn->code) == BPF_STX &&
		    ((BPF_MODE(insn->code) != BPF_MEM &&
		      BPF_MODE(insn->code) != BPF_XADD) || insn->imm != 0)) {
			verbose(env, "BPF_STX uses reserved fields\n");
			return -EINVAL;
		}

		if (insn[0].code == (BPF_LD | BPF_IMM | BPF_DW)) {
			struct bpf_map *map;
			struct fd f;

			if (i == insn_cnt - 1 || insn[1].code != 0 ||
			    insn[1].dst_reg != 0 || insn[1].src_reg != 0 ||
			    insn[1].off != 0) {
				verbose(env, "invalid bpf_ld_imm64 insn\n");
				return -EINVAL;
			}

			if (insn->src_reg == 0)
				/* valid generic load 64-bit imm */
				goto next_insn;

			if (insn->src_reg != BPF_PSEUDO_MAP_FD) {
				verbose(env,
					"unrecognized bpf_ld_imm64 insn\n");
				return -EINVAL;
			}

			f = fdget(insn->imm);
			map = __bpf_map_get(f);
			if (IS_ERR(map)) {
				verbose(env, "fd %d is not pointing to valid bpf_map\n",
					insn->imm);
				return PTR_ERR(map);
			}

			err = check_map_prog_compatibility(env, map, env->prog);
			if (err) {
				fdput(f);
				return err;
			}

			/* store map pointer inside BPF_LD_IMM64 instruction */
			insn[0].imm = (u32) (unsigned long) map;
			insn[1].imm = ((u64) (unsigned long) map) >> 32;

			/* check whether we recorded this map already */
			for (j = 0; j < env->used_map_cnt; j++)
				if (env->used_maps[j] == map) {
					fdput(f);
					goto next_insn;
				}

			if (env->used_map_cnt >= MAX_USED_MAPS) {
				fdput(f);
				return -E2BIG;
			}

			/* hold the map. If the program is rejected by verifier,
			 * the map will be released by release_maps() or it
			 * will be used by the valid program until it's unloaded
			 * and all maps are released in free_used_maps()
			 */
			map = bpf_map_inc(map, false);
			if (IS_ERR(map)) {
				fdput(f);
				return PTR_ERR(map);
			}
			env->used_maps[env->used_map_cnt++] = map;

			if (map->map_type == BPF_MAP_TYPE_CGROUP_STORAGE &&
			    bpf_cgroup_storage_assign(env->prog, map)) {
				verbose(env,
					"only one cgroup storage is allowed\n");
				fdput(f);
				return -EBUSY;
			}

			fdput(f);
next_insn:
			insn++;
			i++;
			continue;
		}

		/* Basic sanity check before we invest more work here. */
		if (!bpf_opcode_in_insntable(insn->code)) {
			verbose(env, "unknown opcode %02x\n", insn->code);
			return -EINVAL;
		}
	}

	/* now all pseudo BPF_LD_IMM64 instructions load valid
	 * 'struct bpf_map *' into a register instead of user map_fd.
	 * These pointers will be used later by verifier to validate map access.
	 */
	return 0;
}
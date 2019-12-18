#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int level; } ;
struct bpf_verifier_env {size_t subprog_cnt; TYPE_2__ log; int /*<<< orphan*/  allow_ptr_leaks; TYPE_1__* prog; struct bpf_subprog_info* subprog_info; } ;
struct bpf_subprog_info {int start; } ;
struct bpf_insn {int code; scalar_t__ src_reg; int off; scalar_t__ imm; } ;
struct TYPE_3__ {int len; struct bpf_insn* insnsi; } ;

/* Variables and functions */
 int BPF_CALL ; 
 int BPF_CLASS (int) ; 
 int BPF_EXIT ; 
 int BPF_JA ; 
 int BPF_JMP ; 
 int BPF_JMP32 ; 
 int BPF_LOG_LEVEL2 ; 
 int BPF_OP (int) ; 
 scalar_t__ BPF_PSEUDO_CALL ; 
 int EINVAL ; 
 int EPERM ; 
 int add_subprog (struct bpf_verifier_env*,scalar_t__) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,...) ; 

__attribute__((used)) static int check_subprogs(struct bpf_verifier_env *env)
{
	int i, ret, subprog_start, subprog_end, off, cur_subprog = 0;
	struct bpf_subprog_info *subprog = env->subprog_info;
	struct bpf_insn *insn = env->prog->insnsi;
	int insn_cnt = env->prog->len;

	/* Add entry function. */
	ret = add_subprog(env, 0);
	if (ret < 0)
		return ret;

	/* determine subprog starts. The end is one before the next starts */
	for (i = 0; i < insn_cnt; i++) {
		if (insn[i].code != (BPF_JMP | BPF_CALL))
			continue;
		if (insn[i].src_reg != BPF_PSEUDO_CALL)
			continue;
		if (!env->allow_ptr_leaks) {
			verbose(env, "function calls to other bpf functions are allowed for root only\n");
			return -EPERM;
		}
		ret = add_subprog(env, i + insn[i].imm + 1);
		if (ret < 0)
			return ret;
	}

	/* Add a fake 'exit' subprog which could simplify subprog iteration
	 * logic. 'subprog_cnt' should not be increased.
	 */
	subprog[env->subprog_cnt].start = insn_cnt;

	if (env->log.level & BPF_LOG_LEVEL2)
		for (i = 0; i < env->subprog_cnt; i++)
			verbose(env, "func#%d @%d\n", i, subprog[i].start);

	/* now check that all jumps are within the same subprog */
	subprog_start = subprog[cur_subprog].start;
	subprog_end = subprog[cur_subprog + 1].start;
	for (i = 0; i < insn_cnt; i++) {
		u8 code = insn[i].code;

		if (BPF_CLASS(code) != BPF_JMP && BPF_CLASS(code) != BPF_JMP32)
			goto next;
		if (BPF_OP(code) == BPF_EXIT || BPF_OP(code) == BPF_CALL)
			goto next;
		off = i + insn[i].off + 1;
		if (off < subprog_start || off >= subprog_end) {
			verbose(env, "jump out of range from insn %d to %d\n", i, off);
			return -EINVAL;
		}
next:
		if (i == subprog_end - 1) {
			/* to avoid fall-through from one subprog into another
			 * the last insn of the subprog should be either exit
			 * or unconditional jump back
			 */
			if (code != (BPF_JMP | BPF_EXIT) &&
			    code != (BPF_JMP | BPF_JA)) {
				verbose(env, "last insn is not an exit or jmp\n");
				return -EINVAL;
			}
			subprog_start = subprog_end;
			cur_subprog++;
			if (cur_subprog < env->subprog_cnt)
				subprog_end = subprog[cur_subprog + 1].start;
		}
	}
	return 0;
}
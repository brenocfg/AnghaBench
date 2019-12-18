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
typedef  int u32 ;
struct bpf_verifier_state {int jmp_history_cnt; struct bpf_idx_pair* jmp_history; } ;
struct bpf_verifier_env {int /*<<< orphan*/  prev_insn_idx; int /*<<< orphan*/  insn_idx; } ;
struct bpf_idx_pair {int /*<<< orphan*/  prev_idx; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_USER ; 
 struct bpf_idx_pair* krealloc (struct bpf_idx_pair*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int push_jmp_history(struct bpf_verifier_env *env,
			    struct bpf_verifier_state *cur)
{
	u32 cnt = cur->jmp_history_cnt;
	struct bpf_idx_pair *p;

	cnt++;
	p = krealloc(cur->jmp_history, cnt * sizeof(*p), GFP_USER);
	if (!p)
		return -ENOMEM;
	p[cnt - 1].idx = env->insn_idx;
	p[cnt - 1].prev_idx = env->prev_insn_idx;
	cur->jmp_history = p;
	cur->jmp_history_cnt = cnt;
	return 0;
}
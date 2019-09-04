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
struct bpf_verifier_env {struct bpf_insn_aux_data* insn_aux_data; } ;
struct bpf_insn_aux_data {int seen; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 int /*<<< orphan*/  memcpy (struct bpf_insn_aux_data*,struct bpf_insn_aux_data*,int) ; 
 int /*<<< orphan*/  vfree (struct bpf_insn_aux_data*) ; 
 struct bpf_insn_aux_data* vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adjust_insn_aux_data(struct bpf_verifier_env *env, u32 prog_len,
				u32 off, u32 cnt)
{
	struct bpf_insn_aux_data *new_data, *old_data = env->insn_aux_data;
	int i;

	if (cnt == 1)
		return 0;
	new_data = vzalloc(array_size(prog_len,
				      sizeof(struct bpf_insn_aux_data)));
	if (!new_data)
		return -ENOMEM;
	memcpy(new_data, old_data, sizeof(struct bpf_insn_aux_data) * off);
	memcpy(new_data + off + cnt - 1, old_data + off,
	       sizeof(struct bpf_insn_aux_data) * (prog_len - off - cnt + 1));
	for (i = off; i < off + cnt - 1; i++)
		new_data[i].seen = true;
	env->insn_aux_data = new_data;
	vfree(old_data);
	return 0;
}
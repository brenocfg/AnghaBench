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
typedef  size_t u32 ;
struct bpf_verifier_env {struct bpf_insn_aux_data* insn_aux_data; } ;
struct bpf_prog {size_t len; struct bpf_insn* insnsi; } ;
struct bpf_insn_aux_data {int seen; void* zext_dst; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  array_size (size_t,int) ; 
 void* insn_has_def32 (struct bpf_verifier_env*,struct bpf_insn*) ; 
 int /*<<< orphan*/  memcpy (struct bpf_insn_aux_data*,struct bpf_insn_aux_data*,int) ; 
 int /*<<< orphan*/  vfree (struct bpf_insn_aux_data*) ; 
 struct bpf_insn_aux_data* vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adjust_insn_aux_data(struct bpf_verifier_env *env,
				struct bpf_prog *new_prog, u32 off, u32 cnt)
{
	struct bpf_insn_aux_data *new_data, *old_data = env->insn_aux_data;
	struct bpf_insn *insn = new_prog->insnsi;
	u32 prog_len;
	int i;

	/* aux info at OFF always needs adjustment, no matter fast path
	 * (cnt == 1) is taken or not. There is no guarantee INSN at OFF is the
	 * original insn at old prog.
	 */
	old_data[off].zext_dst = insn_has_def32(env, insn + off + cnt - 1);

	if (cnt == 1)
		return 0;
	prog_len = new_prog->len;
	new_data = vzalloc(array_size(prog_len,
				      sizeof(struct bpf_insn_aux_data)));
	if (!new_data)
		return -ENOMEM;
	memcpy(new_data, old_data, sizeof(struct bpf_insn_aux_data) * off);
	memcpy(new_data + off + cnt - 1, old_data + off,
	       sizeof(struct bpf_insn_aux_data) * (prog_len - off - cnt + 1));
	for (i = off; i < off + cnt - 1; i++) {
		new_data[i].seen = true;
		new_data[i].zext_dst = insn_has_def32(env, insn + i);
	}
	env->insn_aux_data = new_data;
	vfree(old_data);
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct bpf_verifier_env {TYPE_2__* prog; } ;
struct bpf_prog_offload_ops {int (* replace_insn ) (struct bpf_verifier_env*,int /*<<< orphan*/ ,struct bpf_insn*) ;} ;
struct bpf_prog_offload {int opt_failed; TYPE_3__* offdev; } ;
struct bpf_insn {int dummy; } ;
struct TYPE_6__ {struct bpf_prog_offload_ops* ops; } ;
struct TYPE_5__ {TYPE_1__* aux; } ;
struct TYPE_4__ {struct bpf_prog_offload* offload; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int stub1 (struct bpf_verifier_env*,int /*<<< orphan*/ ,struct bpf_insn*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void
bpf_prog_offload_replace_insn(struct bpf_verifier_env *env, u32 off,
			      struct bpf_insn *insn)
{
	const struct bpf_prog_offload_ops *ops;
	struct bpf_prog_offload *offload;
	int ret = -EOPNOTSUPP;

	down_read(&bpf_devs_lock);
	offload = env->prog->aux->offload;
	if (offload) {
		ops = offload->offdev->ops;
		if (!offload->opt_failed && ops->replace_insn)
			ret = ops->replace_insn(env, off, insn);
		offload->opt_failed |= ret;
	}
	up_read(&bpf_devs_lock);
}
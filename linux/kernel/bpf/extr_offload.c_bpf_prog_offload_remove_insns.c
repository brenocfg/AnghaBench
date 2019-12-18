#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct bpf_verifier_env {TYPE_4__* prog; } ;
struct bpf_prog_offload {int opt_failed; TYPE_2__* offdev; } ;
struct TYPE_8__ {TYPE_3__* aux; } ;
struct TYPE_7__ {struct bpf_prog_offload* offload; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int (* remove_insns ) (struct bpf_verifier_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int stub1 (struct bpf_verifier_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void
bpf_prog_offload_remove_insns(struct bpf_verifier_env *env, u32 off, u32 cnt)
{
	struct bpf_prog_offload *offload;
	int ret = -EOPNOTSUPP;

	down_read(&bpf_devs_lock);
	offload = env->prog->aux->offload;
	if (offload) {
		if (!offload->opt_failed && offload->offdev->ops->remove_insns)
			ret = offload->offdev->ops->remove_insns(env, off, cnt);
		offload->opt_failed |= ret;
	}
	up_read(&bpf_devs_lock);
}
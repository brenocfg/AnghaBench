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
struct TYPE_5__ {int /*<<< orphan*/  ops; TYPE_4__* prog; } ;
struct netdev_bpf {TYPE_1__ verifier; } ;
struct bpf_verifier_env {TYPE_4__* prog; } ;
struct TYPE_8__ {TYPE_2__* aux; } ;
struct TYPE_7__ {int dev_state; int /*<<< orphan*/  dev_ops; } ;
struct TYPE_6__ {TYPE_3__* offload; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_OFFLOAD_VERIFIER_PREP ; 
 int __bpf_offload_ndo (TYPE_4__*,int /*<<< orphan*/ ,struct netdev_bpf*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int bpf_prog_offload_verifier_prep(struct bpf_verifier_env *env)
{
	struct netdev_bpf data = {};
	int err;

	data.verifier.prog = env->prog;

	rtnl_lock();
	err = __bpf_offload_ndo(env->prog, BPF_OFFLOAD_VERIFIER_PREP, &data);
	if (err)
		goto exit_unlock;

	env->prog->aux->offload->dev_ops = data.verifier.ops;
	env->prog->aux->offload->dev_state = true;
exit_unlock:
	rtnl_unlock();
	return err;
}
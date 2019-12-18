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
struct bpf_verifier_env {TYPE_2__* prog; } ;
struct bpf_prog_offload {TYPE_4__* offdev; } ;
struct TYPE_8__ {TYPE_3__* ops; } ;
struct TYPE_7__ {int (* insn_hook ) (struct bpf_verifier_env*,int,int) ;} ;
struct TYPE_6__ {TYPE_1__* aux; } ;
struct TYPE_5__ {struct bpf_prog_offload* offload; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int stub1 (struct bpf_verifier_env*,int,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int bpf_prog_offload_verify_insn(struct bpf_verifier_env *env,
				 int insn_idx, int prev_insn_idx)
{
	struct bpf_prog_offload *offload;
	int ret = -ENODEV;

	down_read(&bpf_devs_lock);
	offload = env->prog->aux->offload;
	if (offload)
		ret = offload->offdev->ops->insn_hook(env, insn_idx,
						      prev_insn_idx);
	up_read(&bpf_devs_lock);

	return ret;
}
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
struct bpf_verifier_env {int used_map_cnt; int /*<<< orphan*/ * used_maps; TYPE_2__* prog; } ;
struct TYPE_4__ {TYPE_1__* aux; } ;
struct TYPE_3__ {scalar_t__ cgroup_storage; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_cgroup_storage_release (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  bpf_map_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_maps(struct bpf_verifier_env *env)
{
	int i;

	if (env->prog->aux->cgroup_storage)
		bpf_cgroup_storage_release(env->prog,
					   env->prog->aux->cgroup_storage);

	for (i = 0; i < env->used_map_cnt; i++)
		bpf_map_put(env->used_maps[i]);
}
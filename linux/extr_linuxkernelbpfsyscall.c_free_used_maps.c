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
struct bpf_prog_aux {int used_map_cnt; int /*<<< orphan*/ * used_maps; scalar_t__ cgroup_storage; int /*<<< orphan*/  prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_cgroup_storage_release (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bpf_map_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_used_maps(struct bpf_prog_aux *aux)
{
	int i;

	if (aux->cgroup_storage)
		bpf_cgroup_storage_release(aux->prog, aux->cgroup_storage);

	for (i = 0; i < aux->used_map_cnt; i++)
		bpf_map_put(aux->used_maps[i]);

	kfree(aux->used_maps);
}
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
struct nsim_bpf_bound_map {int /*<<< orphan*/  mutex; TYPE_2__* entry; } ;
struct TYPE_3__ {scalar_t__ map_type; } ;
struct bpf_offloaded_map {TYPE_1__ map; struct nsim_bpf_bound_map* dev_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ BPF_MAP_TYPE_ARRAY ; 
 int EINVAL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nsim_map_key_find (struct bpf_offloaded_map*,void*) ; 

__attribute__((used)) static int nsim_map_delete_elem(struct bpf_offloaded_map *offmap, void *key)
{
	struct nsim_bpf_bound_map *nmap = offmap->dev_priv;
	int idx;

	if (offmap->map.map_type == BPF_MAP_TYPE_ARRAY)
		return -EINVAL;

	mutex_lock(&nmap->mutex);

	idx = nsim_map_key_find(offmap, key);
	if (idx >= 0) {
		kfree(nmap->entry[idx].key);
		kfree(nmap->entry[idx].value);
		memset(&nmap->entry[idx], 0, sizeof(nmap->entry[idx]));
	}

	mutex_unlock(&nmap->mutex);

	return idx < 0 ? idx : 0;
}
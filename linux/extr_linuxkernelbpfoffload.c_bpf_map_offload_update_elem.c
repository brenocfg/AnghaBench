#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct bpf_offloaded_map {TYPE_1__* dev_ops; scalar_t__ netdev; } ;
struct bpf_map {int dummy; } ;
struct TYPE_2__ {int (* map_update_elem ) (struct bpf_offloaded_map*,void*,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_EXIST ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct bpf_offloaded_map* map_to_offmap (struct bpf_map*) ; 
 int stub1 (struct bpf_offloaded_map*,void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int bpf_map_offload_update_elem(struct bpf_map *map,
				void *key, void *value, u64 flags)
{
	struct bpf_offloaded_map *offmap = map_to_offmap(map);
	int ret = -ENODEV;

	if (unlikely(flags > BPF_EXIST))
		return -EINVAL;

	down_read(&bpf_devs_lock);
	if (offmap->netdev)
		ret = offmap->dev_ops->map_update_elem(offmap, key, value,
						       flags);
	up_read(&bpf_devs_lock);

	return ret;
}
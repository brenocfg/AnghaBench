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
struct bpf_prog {int dummy; } ;
struct bpf_offloaded_map {int /*<<< orphan*/  netdev; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int __bpf_offload_dev_match (struct bpf_prog*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  bpf_map_is_dev_bound (struct bpf_map*) ; 
 int bpf_map_offload_neutral (struct bpf_map*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct bpf_offloaded_map* map_to_offmap (struct bpf_map*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

bool bpf_offload_prog_map_match(struct bpf_prog *prog, struct bpf_map *map)
{
	struct bpf_offloaded_map *offmap;
	bool ret;

	if (!bpf_map_is_dev_bound(map))
		return bpf_map_offload_neutral(map);
	offmap = map_to_offmap(map);

	down_read(&bpf_devs_lock);
	ret = __bpf_offload_dev_match(prog, offmap->netdev);
	up_read(&bpf_devs_lock);

	return ret;
}
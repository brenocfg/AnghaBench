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
struct bpf_offloaded_map {scalar_t__ netdev; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bpf_map_offload_destroy (struct bpf_offloaded_map*) ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bpf_offloaded_map*) ; 
 struct bpf_offloaded_map* map_to_offmap (struct bpf_map*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void bpf_map_offload_map_free(struct bpf_map *map)
{
	struct bpf_offloaded_map *offmap = map_to_offmap(map);

	rtnl_lock();
	down_write(&bpf_devs_lock);
	if (offmap->netdev)
		__bpf_map_offload_destroy(offmap);
	up_write(&bpf_devs_lock);
	rtnl_unlock();

	kfree(offmap);
}
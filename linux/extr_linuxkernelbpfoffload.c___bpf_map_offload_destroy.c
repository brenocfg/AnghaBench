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
struct bpf_offloaded_map {int /*<<< orphan*/ * netdev; int /*<<< orphan*/  offloads; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_OFFLOAD_MAP_FREE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_map_free_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bpf_map_offload_ndo (struct bpf_offloaded_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __bpf_map_offload_destroy(struct bpf_offloaded_map *offmap)
{
	WARN_ON(bpf_map_offload_ndo(offmap, BPF_OFFLOAD_MAP_FREE));
	/* Make sure BPF_MAP_GET_NEXT_ID can't find this dead map */
	bpf_map_free_id(&offmap->map, true);
	list_del_init(&offmap->offloads);
	offmap->netdev = NULL;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct bpf_map {int map_type; } ;

/* Variables and functions */
#define  BPF_MAP_TYPE_CPUMAP 131 
#define  BPF_MAP_TYPE_DEVMAP 130 
#define  BPF_MAP_TYPE_DEVMAP_HASH 129 
#define  BPF_MAP_TYPE_XSKMAP 128 
 void* __cpu_map_lookup_elem (struct bpf_map*,int /*<<< orphan*/ ) ; 
 void* __dev_map_hash_lookup_elem (struct bpf_map*,int /*<<< orphan*/ ) ; 
 void* __dev_map_lookup_elem (struct bpf_map*,int /*<<< orphan*/ ) ; 
 void* __xsk_map_lookup_elem (struct bpf_map*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *__xdp_map_lookup_elem(struct bpf_map *map, u32 index)
{
	switch (map->map_type) {
	case BPF_MAP_TYPE_DEVMAP:
		return __dev_map_lookup_elem(map, index);
	case BPF_MAP_TYPE_DEVMAP_HASH:
		return __dev_map_hash_lookup_elem(map, index);
	case BPF_MAP_TYPE_CPUMAP:
		return __cpu_map_lookup_elem(map, index);
	case BPF_MAP_TYPE_XSKMAP:
		return __xsk_map_lookup_elem(map, index);
	default:
		return NULL;
	}
}
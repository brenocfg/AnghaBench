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
struct bpf_redirect_info {struct bpf_map* map_to_flush; } ;
struct bpf_map {int map_type; } ;

/* Variables and functions */
#define  BPF_MAP_TYPE_CPUMAP 131 
#define  BPF_MAP_TYPE_DEVMAP 130 
#define  BPF_MAP_TYPE_DEVMAP_HASH 129 
#define  BPF_MAP_TYPE_XSKMAP 128 
 int /*<<< orphan*/  __cpu_map_flush (struct bpf_map*) ; 
 int /*<<< orphan*/  __dev_map_flush (struct bpf_map*) ; 
 int /*<<< orphan*/  __xsk_map_flush (struct bpf_map*) ; 
 int /*<<< orphan*/  bpf_redirect_info ; 
 struct bpf_redirect_info* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void xdp_do_flush_map(void)
{
	struct bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);
	struct bpf_map *map = ri->map_to_flush;

	ri->map_to_flush = NULL;
	if (map) {
		switch (map->map_type) {
		case BPF_MAP_TYPE_DEVMAP:
		case BPF_MAP_TYPE_DEVMAP_HASH:
			__dev_map_flush(map);
			break;
		case BPF_MAP_TYPE_CPUMAP:
			__cpu_map_flush(map);
			break;
		case BPF_MAP_TYPE_XSKMAP:
			__xsk_map_flush(map);
			break;
		default:
			break;
		}
	}
}
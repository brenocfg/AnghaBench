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
struct TYPE_2__ {int map_flags; int numa_node; scalar_t__ type; size_t inner_map_idx; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; } ;
struct bpf_map_data {int fd; char* name; TYPE_1__ def; } ;
typedef  int /*<<< orphan*/  (* fixup_map_cb ) (struct bpf_map_data*,int) ;

/* Variables and functions */
 int BPF_F_NUMA_NODE ; 
 scalar_t__ BPF_MAP_TYPE_ARRAY_OF_MAPS ; 
 scalar_t__ BPF_MAP_TYPE_HASH_OF_MAPS ; 
 scalar_t__ BPF_MAP_TYPE_PROG_ARRAY ; 
 void* bpf_create_map_in_map_node (scalar_t__,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 void* bpf_create_map_node (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int errno ; 
 void** map_fd ; 
 int /*<<< orphan*/  printf (char*,int,char*,int,char*) ; 
 void* prog_array_fd ; 
 char* strerror (int) ; 

__attribute__((used)) static int load_maps(struct bpf_map_data *maps, int nr_maps,
		     fixup_map_cb fixup_map)
{
	int i, numa_node;

	for (i = 0; i < nr_maps; i++) {
		if (fixup_map) {
			fixup_map(&maps[i], i);
			/* Allow userspace to assign map FD prior to creation */
			if (maps[i].fd != -1) {
				map_fd[i] = maps[i].fd;
				continue;
			}
		}

		numa_node = maps[i].def.map_flags & BPF_F_NUMA_NODE ?
			maps[i].def.numa_node : -1;

		if (maps[i].def.type == BPF_MAP_TYPE_ARRAY_OF_MAPS ||
		    maps[i].def.type == BPF_MAP_TYPE_HASH_OF_MAPS) {
			int inner_map_fd = map_fd[maps[i].def.inner_map_idx];

			map_fd[i] = bpf_create_map_in_map_node(maps[i].def.type,
							maps[i].name,
							maps[i].def.key_size,
							inner_map_fd,
							maps[i].def.max_entries,
							maps[i].def.map_flags,
							numa_node);
		} else {
			map_fd[i] = bpf_create_map_node(maps[i].def.type,
							maps[i].name,
							maps[i].def.key_size,
							maps[i].def.value_size,
							maps[i].def.max_entries,
							maps[i].def.map_flags,
							numa_node);
		}
		if (map_fd[i] < 0) {
			printf("failed to create map %d (%s): %d %s\n",
			       i, maps[i].name, errno, strerror(errno));
			return 1;
		}
		maps[i].fd = map_fd[i];

		if (maps[i].def.type == BPF_MAP_TYPE_PROG_ARRAY)
			prog_array_fd = map_fd[i];
	}
	return 0;
}
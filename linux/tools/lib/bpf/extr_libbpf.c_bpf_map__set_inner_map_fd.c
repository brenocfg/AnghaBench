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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct bpf_map {int inner_map_fd; TYPE_1__ def; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bpf_map_type__is_map_in_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

int bpf_map__set_inner_map_fd(struct bpf_map *map, int fd)
{
	if (!bpf_map_type__is_map_in_map(map->def.type)) {
		pr_warning("error: unsupported map type\n");
		return -EINVAL;
	}
	if (map->inner_map_fd != -1) {
		pr_warning("error: inner_map_fd already specified\n");
		return -EINVAL;
	}
	map->inner_map_fd = fd;
	return 0;
}
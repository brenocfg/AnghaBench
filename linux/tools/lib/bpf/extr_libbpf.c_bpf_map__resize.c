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
struct TYPE_2__ {scalar_t__ max_entries; } ;
struct bpf_map {scalar_t__ fd; TYPE_1__ def; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 

int bpf_map__resize(struct bpf_map *map, __u32 max_entries)
{
	if (!map || !max_entries)
		return -EINVAL;

	/* If map already created, its attributes can't be changed. */
	if (map->fd >= 0)
		return -EBUSY;

	map->def.max_entries = max_entries;

	return 0;
}
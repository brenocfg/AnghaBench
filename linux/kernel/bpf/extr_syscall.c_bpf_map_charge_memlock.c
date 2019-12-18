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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pages; int /*<<< orphan*/  user; } ;
struct bpf_map {TYPE_1__ memory; } ;

/* Variables and functions */
 int bpf_charge_memlock (int /*<<< orphan*/ ,scalar_t__) ; 

int bpf_map_charge_memlock(struct bpf_map *map, u32 pages)
{
	int ret;

	ret = bpf_charge_memlock(map->memory.user, pages);
	if (ret)
		return ret;
	map->memory.pages += pages;
	return ret;
}
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
typedef  scalar_t__ u32 ;
struct bpf_map {int /*<<< orphan*/  pages; int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_uncharge_memlock (int /*<<< orphan*/ ,scalar_t__) ; 

void bpf_map_uncharge_memlock(struct bpf_map *map, u32 pages)
{
	bpf_uncharge_memlock(map->user, pages);
	map->pages -= pages;
}
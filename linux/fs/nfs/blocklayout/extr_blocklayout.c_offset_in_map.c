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
typedef  scalar_t__ u64 ;
struct pnfs_block_dev_map {scalar_t__ start; scalar_t__ len; } ;

/* Variables and functions */

__attribute__((used)) static bool offset_in_map(u64 offset, struct pnfs_block_dev_map *map)
{
	return offset >= map->start && offset < map->start + map->len;
}
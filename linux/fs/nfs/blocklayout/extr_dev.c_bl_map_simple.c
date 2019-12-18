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
typedef  int /*<<< orphan*/  u64 ;
struct pnfs_block_dev_map {int /*<<< orphan*/  bdev; int /*<<< orphan*/  disk_offset; int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;
struct pnfs_block_dev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  disk_offset; int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;

/* Variables and functions */

__attribute__((used)) static bool bl_map_simple(struct pnfs_block_dev *dev, u64 offset,
		struct pnfs_block_dev_map *map)
{
	map->start = dev->start;
	map->len = dev->len;
	map->disk_offset = dev->disk_offset;
	map->bdev = dev->bdev;
	return true;
}
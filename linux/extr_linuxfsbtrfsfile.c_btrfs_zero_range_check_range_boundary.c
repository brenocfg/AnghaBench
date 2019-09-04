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
struct inode {int dummy; } ;
struct extent_map {scalar_t__ block_start; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  EXTENT_FLAG_PREALLOC ; 
 scalar_t__ EXTENT_MAP_HOLE ; 
 scalar_t__ IS_ERR (struct extent_map*) ; 
 int PTR_ERR (struct extent_map*) ; 
 int RANGE_BOUNDARY_HOLE ; 
 int RANGE_BOUNDARY_PREALLOC_EXTENT ; 
 int RANGE_BOUNDARY_WRITTEN_EXTENT ; 
 struct extent_map* btrfs_get_extent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_inode_sectorsize (struct inode*) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 int /*<<< orphan*/  round_down (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_zero_range_check_range_boundary(struct inode *inode,
						 u64 offset)
{
	const u64 sectorsize = btrfs_inode_sectorsize(inode);
	struct extent_map *em;
	int ret;

	offset = round_down(offset, sectorsize);
	em = btrfs_get_extent(BTRFS_I(inode), NULL, 0, offset, sectorsize, 0);
	if (IS_ERR(em))
		return PTR_ERR(em);

	if (em->block_start == EXTENT_MAP_HOLE)
		ret = RANGE_BOUNDARY_HOLE;
	else if (test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
		ret = RANGE_BOUNDARY_PREALLOC_EXTENT;
	else
		ret = RANGE_BOUNDARY_WRITTEN_EXTENT;

	free_extent_map(em);
	return ret;
}
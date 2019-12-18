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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_map {scalar_t__ block_start; scalar_t__ start; scalar_t__ len; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_I (struct inode*) ; 
 scalar_t__ EXTENT_MAP_HOLE ; 
 scalar_t__ IS_ERR (struct extent_map*) ; 
 int PTR_ERR (struct extent_map*) ; 
 struct extent_map* btrfs_get_extent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 int /*<<< orphan*/  round_down (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_up (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_first_non_hole(struct inode *inode, u64 *start, u64 *len)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct extent_map *em;
	int ret = 0;

	em = btrfs_get_extent(BTRFS_I(inode), NULL, 0,
			      round_down(*start, fs_info->sectorsize),
			      round_up(*len, fs_info->sectorsize), 0);
	if (IS_ERR(em))
		return PTR_ERR(em);

	/* Hole or vacuum extent(only exists in no-hole mode) */
	if (em->block_start == EXTENT_MAP_HOLE) {
		ret = 1;
		*len = em->start + em->len > *start + *len ?
		       0 : *start + *len - em->start - em->len;
		*start = em->start + em->len;
	}
	free_extent_map(em);
	return ret;
}
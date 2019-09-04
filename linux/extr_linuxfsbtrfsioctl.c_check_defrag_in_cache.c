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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct inode {int dummy; } ;
struct extent_map_tree {int /*<<< orphan*/  lock; } ;
struct extent_map {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct TYPE_2__ {struct extent_map_tree extent_tree; struct extent_io_tree io_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  EXTENT_DELALLOC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ count_range_bits (struct extent_io_tree*,scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ extent_map_end (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 struct extent_map* lookup_extent_mapping (struct extent_map_tree*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_defrag_in_cache(struct inode *inode, u64 offset, u32 thresh)
{
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct extent_map *em = NULL;
	struct extent_map_tree *em_tree = &BTRFS_I(inode)->extent_tree;
	u64 end;

	read_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, offset, PAGE_SIZE);
	read_unlock(&em_tree->lock);

	if (em) {
		end = extent_map_end(em);
		free_extent_map(em);
		if (end - offset > thresh)
			return 0;
	}
	/* if we already have a nice delalloc here, just stop */
	thresh /= 2;
	end = count_range_bits(io_tree, &offset, offset + thresh,
			       thresh, EXTENT_DELALLOC, 1);
	if (end >= thresh)
		return 0;
	return 1;
}
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
struct extent_map {scalar_t__ block_start; scalar_t__ start; scalar_t__ block_len; scalar_t__ orig_start; scalar_t__ len; int /*<<< orphan*/  flags; int /*<<< orphan*/ * bdev; } ;
struct btrfs_inode {int /*<<< orphan*/  io_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct extent_map*) ; 
 int ENOMEM ; 
 struct extent_map* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXTENT_DELALLOC ; 
 int /*<<< orphan*/  EXTENT_FLAG_PREALLOC ; 
 scalar_t__ EXTENT_MAP_DELALLOC ; 
 scalar_t__ EXTENT_MAP_HOLE ; 
 scalar_t__ IS_ERR (struct extent_map*) ; 
 struct extent_map* alloc_extent_map () ; 
 struct extent_map* btrfs_get_extent (struct btrfs_inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ count_range_bits (int /*<<< orphan*/ *,scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ extent_map_end (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct extent_map *btrfs_get_extent_fiemap(struct btrfs_inode *inode,
					   u64 start, u64 len)
{
	struct extent_map *em;
	struct extent_map *hole_em = NULL;
	u64 delalloc_start = start;
	u64 end;
	u64 delalloc_len;
	u64 delalloc_end;
	int err = 0;

	em = btrfs_get_extent(inode, NULL, 0, start, len, 0);
	if (IS_ERR(em))
		return em;
	/*
	 * If our em maps to:
	 * - a hole or
	 * - a pre-alloc extent,
	 * there might actually be delalloc bytes behind it.
	 */
	if (em->block_start != EXTENT_MAP_HOLE &&
	    !test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
		return em;
	else
		hole_em = em;

	/* check to see if we've wrapped (len == -1 or similar) */
	end = start + len;
	if (end < start)
		end = (u64)-1;
	else
		end -= 1;

	em = NULL;

	/* ok, we didn't find anything, lets look for delalloc */
	delalloc_len = count_range_bits(&inode->io_tree, &delalloc_start,
				 end, len, EXTENT_DELALLOC, 1);
	delalloc_end = delalloc_start + delalloc_len;
	if (delalloc_end < delalloc_start)
		delalloc_end = (u64)-1;

	/*
	 * We didn't find anything useful, return the original results from
	 * get_extent()
	 */
	if (delalloc_start > end || delalloc_end <= start) {
		em = hole_em;
		hole_em = NULL;
		goto out;
	}

	/*
	 * Adjust the delalloc_start to make sure it doesn't go backwards from
	 * the start they passed in
	 */
	delalloc_start = max(start, delalloc_start);
	delalloc_len = delalloc_end - delalloc_start;

	if (delalloc_len > 0) {
		u64 hole_start;
		u64 hole_len;
		const u64 hole_end = extent_map_end(hole_em);

		em = alloc_extent_map();
		if (!em) {
			err = -ENOMEM;
			goto out;
		}
		em->bdev = NULL;

		ASSERT(hole_em);
		/*
		 * When btrfs_get_extent can't find anything it returns one
		 * huge hole
		 *
		 * Make sure what it found really fits our range, and adjust to
		 * make sure it is based on the start from the caller
		 */
		if (hole_end <= start || hole_em->start > end) {
		       free_extent_map(hole_em);
		       hole_em = NULL;
		} else {
		       hole_start = max(hole_em->start, start);
		       hole_len = hole_end - hole_start;
		}

		if (hole_em && delalloc_start > hole_start) {
			/*
			 * Our hole starts before our delalloc, so we have to
			 * return just the parts of the hole that go until the
			 * delalloc starts
			 */
			em->len = min(hole_len, delalloc_start - hole_start);
			em->start = hole_start;
			em->orig_start = hole_start;
			/*
			 * Don't adjust block start at all, it is fixed at
			 * EXTENT_MAP_HOLE
			 */
			em->block_start = hole_em->block_start;
			em->block_len = hole_len;
			if (test_bit(EXTENT_FLAG_PREALLOC, &hole_em->flags))
				set_bit(EXTENT_FLAG_PREALLOC, &em->flags);
		} else {
			/*
			 * Hole is out of passed range or it starts after
			 * delalloc range
			 */
			em->start = delalloc_start;
			em->len = delalloc_len;
			em->orig_start = delalloc_start;
			em->block_start = EXTENT_MAP_DELALLOC;
			em->block_len = delalloc_len;
		}
	} else {
		return hole_em;
	}
out:

	free_extent_map(hole_em);
	if (err) {
		free_extent_map(em);
		return ERR_PTR(err);
	}
	return em;
}
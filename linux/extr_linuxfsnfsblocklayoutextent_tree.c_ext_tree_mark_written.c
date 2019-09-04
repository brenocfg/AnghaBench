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
struct rb_root {int dummy; } ;
struct pnfs_block_layout {scalar_t__ bl_lwb; int /*<<< orphan*/  bl_ext_lock; int /*<<< orphan*/  bl_ext_ro; struct rb_root bl_ext_rw; } ;
struct pnfs_block_extent {scalar_t__ be_f_offset; scalar_t__ be_state; scalar_t__ be_tag; int /*<<< orphan*/  be_length; int /*<<< orphan*/  be_v_offset; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ EXTENT_WRITTEN ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ PNFS_BLOCK_INVALID_DATA ; 
 int /*<<< orphan*/  __ext_put_deviceids (int /*<<< orphan*/ *) ; 
 int __ext_tree_remove (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 struct pnfs_block_extent* __ext_tree_search (struct rb_root*,scalar_t__) ; 
 scalar_t__ ext_can_merge (struct pnfs_block_extent*,struct pnfs_block_extent*) ; 
 scalar_t__ ext_f_end (struct pnfs_block_extent*) ; 
 struct pnfs_block_extent* ext_tree_next (struct pnfs_block_extent*) ; 
 struct pnfs_block_extent* ext_tree_prev (struct pnfs_block_extent*) ; 
 int ext_tree_split (struct rb_root*,struct pnfs_block_extent*,scalar_t__) ; 
 struct pnfs_block_extent* ext_try_to_merge_left (struct rb_root*,struct pnfs_block_extent*) ; 
 struct pnfs_block_extent* ext_try_to_merge_right (struct rb_root*,struct pnfs_block_extent*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp ; 

int
ext_tree_mark_written(struct pnfs_block_layout *bl, sector_t start,
		sector_t len, u64 lwb)
{
	struct rb_root *root = &bl->bl_ext_rw;
	sector_t end = start + len;
	struct pnfs_block_extent *be;
	int err = 0;
	LIST_HEAD(tmp);

	spin_lock(&bl->bl_ext_lock);
	/*
	 * First remove all COW extents or holes from written to range.
	 */
	err = __ext_tree_remove(&bl->bl_ext_ro, start, end, &tmp);
	if (err)
		goto out;

	/*
	 * Then mark all invalid extents in the range as written to.
	 */
	for (be = __ext_tree_search(root, start); be; be = ext_tree_next(be)) {
		if (be->be_f_offset >= end)
			break;

		if (be->be_state != PNFS_BLOCK_INVALID_DATA || be->be_tag)
			continue;

		if (be->be_f_offset < start) {
			struct pnfs_block_extent *left = ext_tree_prev(be);

			if (left && ext_can_merge(left, be)) {
				sector_t diff = start - be->be_f_offset;

				left->be_length += diff;

				be->be_f_offset += diff;
				be->be_v_offset += diff;
				be->be_length -= diff;
			} else {
				err = ext_tree_split(root, be, start);
				if (err)
					goto out;
			}
		}

		if (ext_f_end(be) > end) {
			struct pnfs_block_extent *right = ext_tree_next(be);

			if (right && ext_can_merge(be, right)) {
				sector_t diff = end - be->be_f_offset;

				be->be_length -= diff;

				right->be_f_offset -= diff;
				right->be_v_offset -= diff;
				right->be_length += diff;
			} else {
				err = ext_tree_split(root, be, end);
				if (err)
					goto out;
			}
		}

		if (be->be_f_offset >= start && ext_f_end(be) <= end) {
			be->be_tag = EXTENT_WRITTEN;
			be = ext_try_to_merge_left(root, be);
			be = ext_try_to_merge_right(root, be);
		}
	}
out:
	if (bl->bl_lwb < lwb)
		bl->bl_lwb = lwb;
	spin_unlock(&bl->bl_ext_lock);

	__ext_put_deviceids(&tmp);
	return err;
}
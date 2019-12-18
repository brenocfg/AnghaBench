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
struct rb_root {int dummy; } ;
struct pnfs_block_extent {scalar_t__ be_f_offset; scalar_t__ be_v_offset; scalar_t__ be_length; scalar_t__ be_state; int /*<<< orphan*/  be_list; int /*<<< orphan*/  be_node; int /*<<< orphan*/  be_device; int /*<<< orphan*/  be_tag; } ;
struct list_head {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PNFS_BLOCK_NONE_DATA ; 
 int /*<<< orphan*/  __ext_tree_insert (struct rb_root*,struct pnfs_block_extent*,int) ; 
 struct pnfs_block_extent* __ext_tree_search (struct rb_root*,scalar_t__) ; 
 scalar_t__ ext_f_end (struct pnfs_block_extent*) ; 
 struct pnfs_block_extent* ext_tree_next (struct pnfs_block_extent*) ; 
 struct pnfs_block_extent* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  nfs4_get_deviceid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,struct rb_root*) ; 

__attribute__((used)) static int
__ext_tree_remove(struct rb_root *root,
		sector_t start, sector_t end, struct list_head *tmp)
{
	struct pnfs_block_extent *be;
	sector_t len1 = 0, len2 = 0;
	sector_t orig_v_offset;
	sector_t orig_len;

	be = __ext_tree_search(root, start);
	if (!be)
		return 0;
	if (be->be_f_offset >= end)
		return 0;

	orig_v_offset = be->be_v_offset;
	orig_len = be->be_length;

	if (start > be->be_f_offset)
		len1 = start - be->be_f_offset;
	if (ext_f_end(be) > end)
		len2 = ext_f_end(be) - end;

	if (len2 > 0) {
		if (len1 > 0) {
			struct pnfs_block_extent *new;

			new = kzalloc(sizeof(*new), GFP_ATOMIC);
			if (!new)
				return -ENOMEM;

			be->be_length = len1;

			new->be_f_offset = end;
			if (be->be_state != PNFS_BLOCK_NONE_DATA) {
				new->be_v_offset =
					orig_v_offset + orig_len - len2;
			}
			new->be_length = len2;
			new->be_state = be->be_state;
			new->be_tag = be->be_tag;
			new->be_device = nfs4_get_deviceid(be->be_device);

			__ext_tree_insert(root, new, true);
		} else {
			be->be_f_offset = end;
			if (be->be_state != PNFS_BLOCK_NONE_DATA) {
				be->be_v_offset =
					orig_v_offset + orig_len - len2;
			}
			be->be_length = len2;
		}
	} else {
		if (len1 > 0) {
			be->be_length = len1;
			be = ext_tree_next(be);
		}

		while (be && ext_f_end(be) <= end) {
			struct pnfs_block_extent *next = ext_tree_next(be);

			rb_erase(&be->be_node, root);
			list_add_tail(&be->be_list, tmp);
			be = next;
		}

		if (be && be->be_f_offset < end) {
			len1 = ext_f_end(be) - end;
			be->be_f_offset = end;
			if (be->be_state != PNFS_BLOCK_NONE_DATA)
				be->be_v_offset += be->be_length - len1;
			be->be_length = len1;
		}
	}

	return 0;
}
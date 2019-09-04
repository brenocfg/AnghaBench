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
struct rb_root {struct rb_node* rb_node; } ;
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct pnfs_block_extent {scalar_t__ be_f_offset; scalar_t__ be_state; int /*<<< orphan*/  be_device; int /*<<< orphan*/  be_node; scalar_t__ be_length; int /*<<< orphan*/  be_v_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ PNFS_BLOCK_NONE_DATA ; 
 scalar_t__ ext_can_merge (struct pnfs_block_extent*,struct pnfs_block_extent*) ; 
 scalar_t__ ext_f_end (struct pnfs_block_extent*) ; 
 struct pnfs_block_extent* ext_node (struct rb_node*) ; 
 struct pnfs_block_extent* ext_try_to_merge_left (struct rb_root*,struct pnfs_block_extent*) ; 
 struct pnfs_block_extent* ext_try_to_merge_right (struct rb_root*,struct pnfs_block_extent*) ; 
 int /*<<< orphan*/  kfree (struct pnfs_block_extent*) ; 
 int /*<<< orphan*/  nfs4_put_deviceid_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_insert_color (int /*<<< orphan*/ *,struct rb_root*) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 

__attribute__((used)) static void
__ext_tree_insert(struct rb_root *root,
		struct pnfs_block_extent *new, bool merge_ok)
{
	struct rb_node **p = &root->rb_node, *parent = NULL;
	struct pnfs_block_extent *be;

	while (*p) {
		parent = *p;
		be = ext_node(parent);

		if (new->be_f_offset < be->be_f_offset) {
			if (merge_ok && ext_can_merge(new, be)) {
				be->be_f_offset = new->be_f_offset;
				if (be->be_state != PNFS_BLOCK_NONE_DATA)
					be->be_v_offset = new->be_v_offset;
				be->be_length += new->be_length;
				be = ext_try_to_merge_left(root, be);
				goto free_new;
			}
			p = &(*p)->rb_left;
		} else if (new->be_f_offset >= ext_f_end(be)) {
			if (merge_ok && ext_can_merge(be, new)) {
				be->be_length += new->be_length;
				be = ext_try_to_merge_right(root, be);
				goto free_new;
			}
			p = &(*p)->rb_right;
		} else {
			BUG();
		}
	}

	rb_link_node(&new->be_node, parent, p);
	rb_insert_color(&new->be_node, root);
	return;
free_new:
	nfs4_put_deviceid_node(new->be_device);
	kfree(new);
}
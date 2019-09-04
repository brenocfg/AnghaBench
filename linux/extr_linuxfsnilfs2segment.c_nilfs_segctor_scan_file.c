#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nilfs_sc_operations {int /*<<< orphan*/ * collect_bmap; int /*<<< orphan*/ * collect_node; int /*<<< orphan*/ * collect_data; } ;
struct TYPE_3__ {int flags; } ;
struct nilfs_sc_info {TYPE_1__ sc_stage; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_bmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 int NILFS_CF_NODE ; 
 TYPE_2__* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  data_buffers ; 
 int /*<<< orphan*/  nilfs_bmap_lookup_dirty_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t nilfs_lookup_dirty_data_buffers (struct inode*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_lookup_dirty_node_buffers (struct inode*,int /*<<< orphan*/ *) ; 
 int nilfs_segctor_apply_buffers (struct nilfs_sc_info*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t nilfs_segctor_buffer_rest (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_segctor_end_finfo (struct nilfs_sc_info*,struct inode*) ; 
 int /*<<< orphan*/  node_buffers ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_segctor_scan_file(struct nilfs_sc_info *sci,
				   struct inode *inode,
				   const struct nilfs_sc_operations *sc_ops)
{
	LIST_HEAD(data_buffers);
	LIST_HEAD(node_buffers);
	int err;

	if (!(sci->sc_stage.flags & NILFS_CF_NODE)) {
		size_t n, rest = nilfs_segctor_buffer_rest(sci);

		n = nilfs_lookup_dirty_data_buffers(
			inode, &data_buffers, rest + 1, 0, LLONG_MAX);
		if (n > rest) {
			err = nilfs_segctor_apply_buffers(
				sci, inode, &data_buffers,
				sc_ops->collect_data);
			BUG_ON(!err); /* always receive -E2BIG or true error */
			goto break_or_fail;
		}
	}
	nilfs_lookup_dirty_node_buffers(inode, &node_buffers);

	if (!(sci->sc_stage.flags & NILFS_CF_NODE)) {
		err = nilfs_segctor_apply_buffers(
			sci, inode, &data_buffers, sc_ops->collect_data);
		if (unlikely(err)) {
			/* dispose node list */
			nilfs_segctor_apply_buffers(
				sci, inode, &node_buffers, NULL);
			goto break_or_fail;
		}
		sci->sc_stage.flags |= NILFS_CF_NODE;
	}
	/* Collect node */
	err = nilfs_segctor_apply_buffers(
		sci, inode, &node_buffers, sc_ops->collect_node);
	if (unlikely(err))
		goto break_or_fail;

	nilfs_bmap_lookup_dirty_buffers(NILFS_I(inode)->i_bmap, &node_buffers);
	err = nilfs_segctor_apply_buffers(
		sci, inode, &node_buffers, sc_ops->collect_bmap);
	if (unlikely(err))
		goto break_or_fail;

	nilfs_segctor_end_finfo(sci, inode);
	sci->sc_stage.flags &= ~NILFS_CF_NODE;

 break_or_fail:
	return err;
}
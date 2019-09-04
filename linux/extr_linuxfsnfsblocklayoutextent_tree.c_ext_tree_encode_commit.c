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
struct pnfs_block_layout {int /*<<< orphan*/  bl_ext_lock; scalar_t__ bl_lwb; scalar_t__ bl_scsi_layout; int /*<<< orphan*/  bl_ext_rw; } ;
struct pnfs_block_extent {scalar_t__ be_state; scalar_t__ be_tag; } ;
typedef  scalar_t__ __u64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ EXTENT_COMMITTING ; 
 scalar_t__ EXTENT_WRITTEN ; 
 scalar_t__ PNFS_BLOCK_INVALID_DATA ; 
 int /*<<< orphan*/ * encode_block_extent (struct pnfs_block_extent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * encode_scsi_range (struct pnfs_block_extent*,int /*<<< orphan*/ *) ; 
 struct pnfs_block_extent* ext_tree_first (int /*<<< orphan*/ *) ; 
 size_t ext_tree_layoutupdate_size (struct pnfs_block_layout*,size_t) ; 
 struct pnfs_block_extent* ext_tree_next (struct pnfs_block_extent*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext_tree_encode_commit(struct pnfs_block_layout *bl, __be32 *p,
		size_t buffer_size, size_t *count, __u64 *lastbyte)
{
	struct pnfs_block_extent *be;
	int ret = 0;

	spin_lock(&bl->bl_ext_lock);
	for (be = ext_tree_first(&bl->bl_ext_rw); be; be = ext_tree_next(be)) {
		if (be->be_state != PNFS_BLOCK_INVALID_DATA ||
		    be->be_tag != EXTENT_WRITTEN)
			continue;

		(*count)++;
		if (ext_tree_layoutupdate_size(bl, *count) > buffer_size) {
			/* keep counting.. */
			ret = -ENOSPC;
			continue;
		}

		if (bl->bl_scsi_layout)
			p = encode_scsi_range(be, p);
		else
			p = encode_block_extent(be, p);
		be->be_tag = EXTENT_COMMITTING;
	}
	*lastbyte = bl->bl_lwb - 1;
	bl->bl_lwb = 0;
	spin_unlock(&bl->bl_ext_lock);

	return ret;
}
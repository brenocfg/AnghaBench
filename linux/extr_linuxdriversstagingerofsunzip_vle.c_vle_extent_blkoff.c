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
struct z_erofs_vle_decompressed_index {int dummy; } ;
struct inode {int dummy; } ;
struct erofs_vnode {int /*<<< orphan*/  nid; scalar_t__ xattr_isize; scalar_t__ inode_isize; } ;
struct erofs_sb_info {int dummy; } ;
struct erofs_extent_header {int dummy; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 struct erofs_sb_info* EROFS_I_SB (struct inode*) ; 
 struct erofs_vnode* EROFS_V (struct inode*) ; 
 int Z_EROFS_VLE_EXTENT_ALIGN (scalar_t__) ; 
 unsigned int erofs_blkoff (scalar_t__) ; 
 scalar_t__ iloc (struct erofs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int
vle_extent_blkoff(struct inode *inode, pgoff_t index)
{
	struct erofs_sb_info *sbi = EROFS_I_SB(inode);
	struct erofs_vnode *vi = EROFS_V(inode);

	unsigned ofs = Z_EROFS_VLE_EXTENT_ALIGN(vi->inode_isize +
		vi->xattr_isize) + sizeof(struct erofs_extent_header) +
		index * sizeof(struct z_erofs_vle_decompressed_index);

	return erofs_blkoff(iloc(sbi, vi->nid) + ofs);
}
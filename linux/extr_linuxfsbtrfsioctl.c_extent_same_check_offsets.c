#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {scalar_t__ i_size; } ;
struct TYPE_8__ {TYPE_3__* root; } ;
struct TYPE_7__ {TYPE_2__* fs_info; } ;
struct TYPE_6__ {TYPE_1__* sb; } ;
struct TYPE_5__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 TYPE_4__* BTRFS_I (struct inode*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int extent_same_check_offsets(struct inode *inode, u64 off, u64 *plen,
				     u64 olen)
{
	u64 len = *plen;
	u64 bs = BTRFS_I(inode)->root->fs_info->sb->s_blocksize;

	if (off + olen > inode->i_size || off + olen < off)
		return -EINVAL;

	/* if we extend to eof, continue to block boundary */
	if (off + len == inode->i_size)
		*plen = len = ALIGN(inode->i_size, bs) - off;

	/* Check that we are block aligned - btrfs_clone() requires this */
	if (!IS_ALIGNED(off, bs) || !IS_ALIGNED(off + len, bs))
		return -EINVAL;

	return 0;
}
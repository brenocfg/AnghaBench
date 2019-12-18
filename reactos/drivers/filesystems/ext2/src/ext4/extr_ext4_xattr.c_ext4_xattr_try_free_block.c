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
struct ext4_xattr_ref {int /*<<< orphan*/  block_loaded; int /*<<< orphan*/  IsOnDiskInodeDirty; TYPE_1__* inode_ref; int /*<<< orphan*/  IrpContext; int /*<<< orphan*/ * block_bh; } ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_4__ {scalar_t__ i_file_acl; } ;
struct TYPE_3__ {TYPE_2__ Inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extents_brelse (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext4_xattr_try_free_block(struct ext4_xattr_ref *xattr_ref)
{
	ext4_fsblk_t xattr_block;
	xattr_block = xattr_ref->inode_ref->Inode.i_file_acl;
	xattr_ref->inode_ref->Inode.i_file_acl = 0;
	extents_brelse(xattr_ref->block_bh);
	xattr_ref->block_bh = NULL;
	ext4_free_blocks(xattr_ref->IrpContext, &xattr_ref->inode_ref->Inode,
		xattr_block, 1, 0);
	xattr_ref->IsOnDiskInodeDirty = TRUE;
	xattr_ref->block_loaded = FALSE;
}
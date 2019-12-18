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
struct inode {int i_blocks; TYPE_1__* i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
struct TYPE_2__ {int s_blocksize; int /*<<< orphan*/  s_priv; } ;
typedef  int /*<<< orphan*/  PEXT2_IRP_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  Ext2FreeBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ext4_free_blocks(void *icb, handle_t *handle, struct inode *inode, void *fake,
		ext4_fsblk_t block, int count, int flags)
{
	Ext2FreeBlock((PEXT2_IRP_CONTEXT)icb, inode->i_sb->s_priv, block, count);
	inode->i_blocks -= count * (inode->i_sb->s_blocksize >> 9);
	return;
}
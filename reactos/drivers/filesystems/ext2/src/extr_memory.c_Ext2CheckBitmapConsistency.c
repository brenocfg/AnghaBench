#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct buffer_head {int dummy; } ;
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {scalar_t__ s_groups_count; } ;
struct TYPE_6__ {int InodeSize; int BlockSize; int /*<<< orphan*/  sb; TYPE_1__ sbi; } ;
typedef  TYPE_2__* PEXT2_VCB ;
typedef  int /*<<< orphan*/  PEXT2_IRP_CONTEXT ;
typedef  int /*<<< orphan*/  PEXT2_GROUP_DESC ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  Ext2CheckSetBlock (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 int INODES_COUNT ; 
 int INODES_PER_GROUP ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ext4_block_bitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_get_group_desc (int /*<<< orphan*/ *,scalar_t__,struct buffer_head**) ; 
 scalar_t__ ext4_inode_bitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_inode_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fini_bh (struct buffer_head**) ; 

BOOLEAN
Ext2CheckBitmapConsistency(PEXT2_IRP_CONTEXT IrpContext, PEXT2_VCB Vcb)
{
    ULONG i, j, InodeBlocks;

    for (i = 0; i < Vcb->sbi.s_groups_count; i++) {

        PEXT2_GROUP_DESC    gd;
        struct buffer_head  *bh = NULL;

        gd = ext4_get_group_desc(&Vcb->sb, i, &bh);
        if (!gd)
            continue;
        Ext2CheckSetBlock(IrpContext, Vcb, ext4_block_bitmap(&Vcb->sb, gd));
        Ext2CheckSetBlock(IrpContext, Vcb, ext4_inode_bitmap(&Vcb->sb, gd));


        if (i == Vcb->sbi.s_groups_count - 1) {
            InodeBlocks = ((INODES_COUNT % INODES_PER_GROUP) *
                           Vcb->InodeSize + Vcb->BlockSize - 1) /
                          (Vcb->BlockSize);
        } else {
            InodeBlocks = (INODES_PER_GROUP * Vcb->InodeSize +
                           Vcb->BlockSize - 1) / (Vcb->BlockSize);
        }

        for (j = 0; j < InodeBlocks; j++ )
            Ext2CheckSetBlock(IrpContext, Vcb, ext4_inode_table(&Vcb->sb, gd) + j);

        fini_bh(&bh);
    }

    return TRUE;
}
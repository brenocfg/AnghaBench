#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_priv; } ;
struct inode {int /*<<< orphan*/  i_priv; struct super_block* i_sb; } ;
typedef  int ULONGLONG ;
struct TYPE_4__ {int Lba; } ;
typedef  int /*<<< orphan*/  PEXT2_VCB ;
typedef  int /*<<< orphan*/  PEXT2_MCB ;
typedef  TYPE_1__* PEXT2_EXTENT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int BLOCK_BITS ; 
 int /*<<< orphan*/  BLOCK_SIZE ; 
 int /*<<< orphan*/  Ext2BuildExtents (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  Ext2FreeExtent (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 

ULONGLONG bmap(struct inode *i, ULONGLONG b)
{
    ULONGLONG lcn = 0;
    struct super_block *s = i->i_sb;

    PEXT2_MCB  Mcb = (PEXT2_MCB)i->i_priv;
    PEXT2_VCB  Vcb = (PEXT2_VCB)s->s_priv;
    PEXT2_EXTENT extent = NULL;
    ULONGLONG  offset = (ULONGLONG)b;
    NTSTATUS   status;

    if (!Mcb || !Vcb) {
        goto errorout;
    }

    offset <<= BLOCK_BITS;
    status = Ext2BuildExtents(
                 NULL,
                 Vcb,
                 Mcb,
                 offset,
                 BLOCK_SIZE,
                 FALSE,
                 &extent
             );

    if (!NT_SUCCESS(status)) {
        goto errorout;
    }

    if (extent == NULL) {
        goto errorout;
    }

    lcn = (unsigned long)(extent->Lba >> BLOCK_BITS);

errorout:

    if (extent) {
        Ext2FreeExtent(extent);
    }

    return lcn;
}
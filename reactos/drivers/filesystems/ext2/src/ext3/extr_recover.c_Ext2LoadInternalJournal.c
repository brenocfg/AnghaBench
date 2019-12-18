#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_13__ {int /*<<< orphan*/ * i_sb; int /*<<< orphan*/  i_ino; } ;
struct TYPE_12__ {TYPE_6__ Inode; } ;
struct TYPE_11__ {int /*<<< orphan*/  sb; } ;
typedef  TYPE_1__* PEXT2_VCB ;
typedef  TYPE_2__* PEXT2_MCB ;

/* Variables and functions */
 int /*<<< orphan*/  DbgBreak () ; 
 TYPE_2__* Ext2AllocateMcb (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ext2FreeMcb (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Ext2LoadInode (TYPE_1__*,TYPE_6__*) ; 

PEXT2_MCB
Ext2LoadInternalJournal(
    PEXT2_VCB         Vcb,
    ULONG             jNo
)
{
    PEXT2_MCB   Jcb = NULL;

    Jcb = Ext2AllocateMcb(Vcb, NULL, NULL, 0);
    if (!Jcb) {
        goto errorout;
    }

    Jcb->Inode.i_ino = jNo;
    Jcb->Inode.i_sb = &Vcb->sb;
    if (!Ext2LoadInode(Vcb, &Jcb->Inode)) {
        DbgBreak();
        Ext2FreeMcb(Vcb, Jcb);
        goto errorout;
    }

errorout:

    return Jcb;
}
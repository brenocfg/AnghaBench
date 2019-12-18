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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int /*<<< orphan*/  Next; int /*<<< orphan*/  TsDrop; } ;
struct TYPE_5__ {int /*<<< orphan*/  FcbList; int /*<<< orphan*/  ReferenceCount; int /*<<< orphan*/  FcbCount; int /*<<< orphan*/  FcbLock; } ;
typedef  TYPE_1__* PEXT2_VCB ;
typedef  TYPE_2__* PEXT2_FCB ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExIsResourceAcquiredExclusiveLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ext2ReferXcb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeQuerySystemTime (int /*<<< orphan*/ *) ; 

VOID
Ext2InsertFcb(PEXT2_VCB Vcb, PEXT2_FCB Fcb)
{
    ASSERT(ExIsResourceAcquiredExclusiveLite(&Vcb->FcbLock));

    KeQuerySystemTime(&Fcb->TsDrop);
    Ext2ReferXcb(&Vcb->FcbCount);
    Ext2ReferXcb(&Vcb->ReferenceCount);
    InsertTailList(&Vcb->FcbList, &Fcb->Next);
}
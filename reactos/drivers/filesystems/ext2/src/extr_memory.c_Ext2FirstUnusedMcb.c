#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_14__ {scalar_t__ QuadPart; } ;
struct TYPE_13__ {scalar_t__ Refercount; int /*<<< orphan*/  Link; struct TYPE_13__* Next; int /*<<< orphan*/  Flags; int /*<<< orphan*/ * Child; int /*<<< orphan*/ * Fcb; } ;
struct TYPE_12__ {scalar_t__ NumOfMcb; int /*<<< orphan*/  McbLock; int /*<<< orphan*/  McbList; } ;
typedef  int /*<<< orphan*/ * PLIST_ENTRY ;
typedef  TYPE_1__* PEXT2_VCB ;
typedef  TYPE_2__* PEXT2_MCB ;
typedef  int LONGLONG ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_2__* CONTAINING_RECORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearLongFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_MCB ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ext2DerefXcb (scalar_t__*) ; 
 int /*<<< orphan*/  Ext2RemoveMcb (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsMcbRoot (TYPE_2__*) ; 
 scalar_t__ IsMcbSymLink (TYPE_2__*) ; 
 int /*<<< orphan*/  KeQuerySystemTime (TYPE_3__*) ; 
 int /*<<< orphan*/  Link ; 
 int /*<<< orphan*/  MCB_VCB_LINK ; 
 int /*<<< orphan*/ * RemoveHeadList (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 

PEXT2_MCB
Ext2FirstUnusedMcb(PEXT2_VCB Vcb, BOOLEAN Wait, ULONG Number)
{
    PEXT2_MCB   Head = NULL;
    PEXT2_MCB   Tail = NULL;
    PEXT2_MCB   Mcb = NULL;
    PLIST_ENTRY List = NULL;
    ULONG       i = 0;
    LARGE_INTEGER   start, now;

    if (!ExAcquireResourceExclusiveLite(&Vcb->McbLock, Wait)) {
        return NULL;
    }

    KeQuerySystemTime(&start);

    while (Number--) {

        BOOLEAN     Skip = TRUE;

        if (IsListEmpty(&Vcb->McbList)) {
            break;
        }

        while (i++ < Vcb->NumOfMcb) {

            KeQuerySystemTime(&now);
            if (now.QuadPart > start.QuadPart + (LONGLONG)10*1000*1000) {
                break;
            }

            List = RemoveHeadList(&Vcb->McbList);
            Mcb = CONTAINING_RECORD(List, EXT2_MCB, Link);
            ASSERT(IsFlagOn(Mcb->Flags, MCB_VCB_LINK));

            if (Mcb->Fcb == NULL && !IsMcbRoot(Mcb) &&
                    Mcb->Refercount == 0 &&
                    (Mcb->Child == NULL || IsMcbSymLink(Mcb))) {

                Ext2RemoveMcb(Vcb, Mcb);
                ClearLongFlag(Mcb->Flags, MCB_VCB_LINK);
                Ext2DerefXcb(&Vcb->NumOfMcb);

                /* attach all Mcb into a chain*/
                if (Head) {
                    ASSERT(Tail != NULL);
                    Tail->Next = Mcb;
                    Tail = Mcb;
                } else {
                    Head = Tail = Mcb;
                }
                Tail->Next = NULL;
                Skip = FALSE;

            } else {

                InsertTailList(&Vcb->McbList, &Mcb->Link);
                Mcb = NULL;
            }
        }

        if (Skip)
            break;
    }

    ExReleaseResourceLite(&Vcb->McbLock);

    return Head;
}
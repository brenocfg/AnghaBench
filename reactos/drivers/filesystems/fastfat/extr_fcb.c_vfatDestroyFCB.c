#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {int /*<<< orphan*/ * Buffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  FcbLookasideList; } ;
struct TYPE_9__ {int /*<<< orphan*/  ParentListHead; int /*<<< orphan*/  MainResource; int /*<<< orphan*/  PagingIoResource; int /*<<< orphan*/  PathNameBuffer; int /*<<< orphan*/  ParentListEntry; int /*<<< orphan*/  Flags; int /*<<< orphan*/  FileLock; int /*<<< orphan*/  RefCount; int /*<<< orphan*/  PathNameU; int /*<<< orphan*/  LongNameU; } ;
typedef  TYPE_1__* PVFATFCB ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__ DebugFile ; 
 int /*<<< orphan*/  ExDeleteResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FCB_IS_FAT ; 
 int /*<<< orphan*/  FCB_IS_VOLUME ; 
 scalar_t__ FsRtlIsNameInExpression (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsRtlUninitializeFileLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 TYPE_4__* VfatGlobalData ; 
 int /*<<< orphan*/  vfatFCBIsRoot (TYPE_1__*) ; 

VOID
vfatDestroyFCB(
    PVFATFCB pFCB)
{
#ifdef KDBG
    if (DebugFile.Buffer != NULL && FsRtlIsNameInExpression(&DebugFile, &pFCB->LongNameU, FALSE, NULL))
    {
        DPRINT1("Destroying: %p (%wZ) %d\n", pFCB, &pFCB->PathNameU, pFCB->RefCount);
    }
#endif

    FsRtlUninitializeFileLock(&pFCB->FileLock);

    if (!vfatFCBIsRoot(pFCB) &&
        !BooleanFlagOn(pFCB->Flags, FCB_IS_FAT) && !BooleanFlagOn(pFCB->Flags, FCB_IS_VOLUME))
    {
        RemoveEntryList(&pFCB->ParentListEntry);
    }
    ExFreePool(pFCB->PathNameBuffer);
    ExDeleteResourceLite(&pFCB->PagingIoResource);
    ExDeleteResourceLite(&pFCB->MainResource);
    ASSERT(IsListEmpty(&pFCB->ParentListHead));
    ExFreeToNPagedLookasideList(&VfatGlobalData->FcbLookasideList, pFCB);
}
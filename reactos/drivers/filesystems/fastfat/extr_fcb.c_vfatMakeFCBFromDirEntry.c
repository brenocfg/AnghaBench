#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_16__ {int RefCount; int /*<<< orphan*/  ParentListEntry; int /*<<< orphan*/  ParentListHead; struct TYPE_16__* parentFcb; } ;
struct TYPE_15__ {int /*<<< orphan*/  ShortNameU; int /*<<< orphan*/  LongNameU; } ;
typedef  TYPE_2__* PVFAT_DIRENTRY_CONTEXT ;
typedef  TYPE_3__* PVFATFCB ;
typedef  int /*<<< orphan*/  PVCB ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TAG_FCB ; 
 int /*<<< orphan*/  vfatAddFCBToTable (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vfatInitFCBFromDirEntry (int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vfatMakeFullName (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_3__* vfatNewFCB (int /*<<< orphan*/ ,TYPE_1__*) ; 

NTSTATUS
vfatMakeFCBFromDirEntry(
    PVCB vcb,
    PVFATFCB directoryFCB,
    PVFAT_DIRENTRY_CONTEXT DirContext,
    PVFATFCB *fileFCB)
{
    PVFATFCB rcFCB;
    UNICODE_STRING NameU;
    NTSTATUS Status;

    Status = vfatMakeFullName(directoryFCB, &DirContext->LongNameU, &DirContext->ShortNameU, &NameU);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    rcFCB = vfatNewFCB(vcb, &NameU);
    vfatInitFCBFromDirEntry(vcb, rcFCB, DirContext);

    rcFCB->RefCount = 1;
    rcFCB->parentFcb = directoryFCB;
    InsertTailList(&directoryFCB->ParentListHead, &rcFCB->ParentListEntry);
    vfatAddFCBToTable(vcb, rcFCB);
    *fileFCB = rcFCB;

    ExFreePoolWithTag(NameU.Buffer, TAG_FCB);
    return STATUS_SUCCESS;
}
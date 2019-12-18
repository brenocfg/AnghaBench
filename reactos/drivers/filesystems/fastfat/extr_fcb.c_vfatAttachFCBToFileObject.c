#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VFATCCB ;
struct TYPE_17__ {int /*<<< orphan*/ * Buffer; } ;
struct TYPE_16__ {int /*<<< orphan*/  CcbLookasideList; } ;
struct TYPE_15__ {int /*<<< orphan*/  IoVPB; } ;
struct TYPE_14__ {int /*<<< orphan*/  Vpb; int /*<<< orphan*/ * FsContext2; TYPE_1__* FsContext; int /*<<< orphan*/ * SectionObjectPointer; } ;
struct TYPE_13__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  PathNameU; int /*<<< orphan*/  SectionObjectPointers; int /*<<< orphan*/  RefCount; int /*<<< orphan*/  LongNameU; } ;
typedef  TYPE_1__* PVFATFCB ;
typedef  int /*<<< orphan*/ * PVFATCCB ;
typedef  TYPE_2__* PFILE_OBJECT ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_8__ DebugFile ; 
 int /*<<< orphan*/ * ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FCB_CLEANED_UP ; 
 int /*<<< orphan*/  FCB_CLOSED ; 
 scalar_t__ FsRtlIsNameInExpression (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 TYPE_7__* VfatGlobalData ; 

NTSTATUS
vfatAttachFCBToFileObject(
    PDEVICE_EXTENSION vcb,
    PVFATFCB fcb,
    PFILE_OBJECT fileObject)
{
    PVFATCCB newCCB;

#ifdef KDBG
    if (DebugFile.Buffer != NULL && FsRtlIsNameInExpression(&DebugFile, &fcb->LongNameU, FALSE, NULL))
    {
        DPRINT1("Attaching %p to %p (%d)\n", fcb, fileObject, fcb->RefCount);
    }
#endif

    newCCB = ExAllocateFromNPagedLookasideList(&VfatGlobalData->CcbLookasideList);
    if (newCCB == NULL)
    {
        return  STATUS_INSUFFICIENT_RESOURCES;
    }
    RtlZeroMemory(newCCB, sizeof (VFATCCB));

    fileObject->SectionObjectPointer = &fcb->SectionObjectPointers;
    fileObject->FsContext = fcb;
    fileObject->FsContext2 = newCCB;
    fileObject->Vpb = vcb->IoVPB;
    DPRINT("file open: fcb:%p PathName:%wZ\n", fcb, &fcb->PathNameU);

#ifdef KDBG
    fcb->Flags &= ~FCB_CLEANED_UP;
    fcb->Flags &= ~FCB_CLOSED;
#endif

    return STATUS_SUCCESS;
}
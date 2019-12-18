#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ Buffer; } ;
typedef  TYPE_3__ UNICODE_STRING ;
struct TYPE_17__ {void* Hash; } ;
struct TYPE_16__ {void* Hash; } ;
struct TYPE_19__ {TYPE_3__ ShortNameU; TYPE_2__ ShortHash; TYPE_3__ DirNameU; TYPE_1__ Hash; TYPE_3__ PathNameU; int /*<<< orphan*/  LongNameU; scalar_t__ PathNameBuffer; } ;
typedef  TYPE_4__* PVFATFCB ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TAG_FCB ; 
 int /*<<< orphan*/  vfatAddFCBToTable (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  vfatDelFCBFromTable (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  vfatMakeFullName (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 
 void* vfatNameHash (void*,TYPE_3__*) ; 
 int /*<<< orphan*/  vfatReleaseFCB (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  vfatSplitPathName (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ vfatVolumeIsFatX (int /*<<< orphan*/ ) ; 

NTSTATUS
vfatSetFCBNewDirName(
    PDEVICE_EXTENSION pVCB,
    PVFATFCB Fcb,
    PVFATFCB ParentFcb)
{
    NTSTATUS Status;
    UNICODE_STRING NewNameU;

    /* Get full path name */
    Status = vfatMakeFullName(ParentFcb, &Fcb->LongNameU, &Fcb->ShortNameU, &NewNameU);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Delete old name */
    if (Fcb->PathNameBuffer)
    {
        ExFreePoolWithTag(Fcb->PathNameBuffer, TAG_FCB);
    }
    Fcb->PathNameU = NewNameU;

    /* Delete from table */
    vfatDelFCBFromTable(pVCB, Fcb);

    /* Split it properly */
    Fcb->PathNameBuffer = Fcb->PathNameU.Buffer;
    Fcb->DirNameU.Buffer = Fcb->PathNameU.Buffer;
    vfatSplitPathName(&Fcb->PathNameU, &Fcb->DirNameU, &Fcb->LongNameU);
    Fcb->Hash.Hash = vfatNameHash(0, &Fcb->PathNameU);
    if (vfatVolumeIsFatX(pVCB))
    {
        Fcb->ShortHash.Hash = Fcb->Hash.Hash;
    }
    else
    {
        Fcb->ShortHash.Hash = vfatNameHash(0, &Fcb->DirNameU);
        Fcb->ShortHash.Hash = vfatNameHash(Fcb->ShortHash.Hash, &Fcb->ShortNameU);
    }

    vfatAddFCBToTable(pVCB, Fcb);
    vfatReleaseFCB(pVCB, ParentFcb);

    return STATUS_SUCCESS;
}
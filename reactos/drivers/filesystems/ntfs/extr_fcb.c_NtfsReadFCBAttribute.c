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
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_14__ {int /*<<< orphan*/  pRecord; } ;
struct TYPE_13__ {int /*<<< orphan*/  MFTIndex; } ;
struct TYPE_12__ {int /*<<< orphan*/  FileRecLookasideList; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PNTFS_VCB ;
typedef  TYPE_2__* PNTFS_FCB ;
typedef  TYPE_3__* PNTFS_ATTR_CONTEXT ;
typedef  int /*<<< orphan*/ * PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AttributeDataLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindAttribute (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  ReadAttribute (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadFileRecord (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseAttributeContext (TYPE_3__*) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TAG_NTFS ; 

NTSTATUS
NtfsReadFCBAttribute(PNTFS_VCB Vcb,
                     PNTFS_FCB pFCB,
                     ULONG Type, 
                     PCWSTR Name,
                     ULONG NameLength,
                     PVOID * Data)
{
    NTSTATUS Status;
    PFILE_RECORD_HEADER FileRecord;
    PNTFS_ATTR_CONTEXT AttrCtxt;
    ULONGLONG AttrLength;

    FileRecord = ExAllocateFromNPagedLookasideList(&Vcb->FileRecLookasideList);
    if (FileRecord == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = ReadFileRecord(Vcb, pFCB->MFTIndex, FileRecord);
    if (!NT_SUCCESS(Status))
    {
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, FileRecord);
        return Status;
    }

    Status = FindAttribute(Vcb, FileRecord, Type, Name, NameLength, &AttrCtxt, NULL);
    if (!NT_SUCCESS(Status))
    {
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, FileRecord);
        return Status;
    }

    AttrLength = AttributeDataLength(AttrCtxt->pRecord);
    *Data = ExAllocatePoolWithTag(NonPagedPool, AttrLength, TAG_NTFS);
    if (*Data == NULL)
    {
        ReleaseAttributeContext(AttrCtxt);
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, FileRecord);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    ReadAttribute(Vcb, AttrCtxt, 0, *Data, AttrLength);

    ReleaseAttributeContext(AttrCtxt);
    ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, FileRecord);

    return STATUS_SUCCESS;
}
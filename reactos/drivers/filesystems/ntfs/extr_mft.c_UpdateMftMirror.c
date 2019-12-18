#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_15__ {int /*<<< orphan*/  pRecord; } ;
struct TYPE_13__ {int BytesPerFileRecord; } ;
struct TYPE_14__ {int /*<<< orphan*/  FileRecLookasideList; TYPE_1__ NtfsInfo; int /*<<< orphan*/  MasterFileTable; } ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  TYPE_2__* PNTFS_VCB ;
typedef  TYPE_3__* PNTFS_ATTR_CONTEXT ;
typedef  int /*<<< orphan*/  PFILE_RECORD_HEADER ;
typedef  scalar_t__ PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  AttributeData ; 
 int AttributeDataLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 scalar_t__ ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindAttribute (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NTFS_FILE_MFTMIRR ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 scalar_t__ ReadAttribute (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ReadFileRecord (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseAttributeContext (TYPE_3__*) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  TAG_NTFS ; 
 int ULONG_MAX ; 
 int /*<<< orphan*/  WriteAttribute (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 

NTSTATUS
UpdateMftMirror(PNTFS_VCB Vcb)
{
    PFILE_RECORD_HEADER MirrorFileRecord;
    PNTFS_ATTR_CONTEXT MirrDataContext;
    PNTFS_ATTR_CONTEXT MftDataContext;
    PCHAR DataBuffer;
    ULONGLONG DataLength;
    NTSTATUS Status;
    ULONG BytesRead;
    ULONG LengthWritten;

    // Allocate memory for the Mft mirror file record
    MirrorFileRecord = ExAllocateFromNPagedLookasideList(&Vcb->FileRecLookasideList);
    if (!MirrorFileRecord)
    {
        DPRINT1("Error: Failed to allocate memory for $MFTMirr!\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // Read the Mft Mirror file record
    Status = ReadFileRecord(Vcb, NTFS_FILE_MFTMIRR, MirrorFileRecord);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ERROR: Failed to read $MFTMirr!\n");
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, MirrorFileRecord);
        return Status;
    }

    // Find the $DATA attribute of $MFTMirr
    Status = FindAttribute(Vcb, MirrorFileRecord, AttributeData, L"", 0, &MirrDataContext, NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ERROR: Couldn't find $DATA attribute!\n");
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, MirrorFileRecord);
        return Status;
    }

    // Find the $DATA attribute of $MFT
    Status = FindAttribute(Vcb, Vcb->MasterFileTable, AttributeData, L"", 0, &MftDataContext, NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ERROR: Couldn't find $DATA attribute!\n");
        ReleaseAttributeContext(MirrDataContext);
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, MirrorFileRecord);
        return Status;
    }

    // Get the size of the mirror's $DATA attribute
    DataLength = AttributeDataLength(MirrDataContext->pRecord);

    ASSERT(DataLength % Vcb->NtfsInfo.BytesPerFileRecord == 0);

    // Create buffer for the mirror's $DATA attribute
    DataBuffer = ExAllocatePoolWithTag(NonPagedPool, DataLength, TAG_NTFS);
    if (!DataBuffer)
    {
        DPRINT1("Error: Couldn't allocate memory for $DATA buffer!\n");
        ReleaseAttributeContext(MftDataContext);
        ReleaseAttributeContext(MirrDataContext);
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, MirrorFileRecord);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    ASSERT(DataLength < ULONG_MAX);

    // Back up the first several entries of the Mft's $DATA Attribute
    BytesRead = ReadAttribute(Vcb, MftDataContext, 0, DataBuffer, (ULONG)DataLength);
    if (BytesRead != (ULONG)DataLength)
    {
        DPRINT1("Error: Failed to read $DATA for $MFTMirr!\n");
        ReleaseAttributeContext(MftDataContext);
        ReleaseAttributeContext(MirrDataContext);
        ExFreePoolWithTag(DataBuffer, TAG_NTFS);
        ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, MirrorFileRecord);
        return STATUS_UNSUCCESSFUL;
    }

    // Write the mirror's $DATA attribute
    Status = WriteAttribute(Vcb,
                             MirrDataContext,
                             0,
                             (PUCHAR)DataBuffer,
                             DataLength,
                             &LengthWritten,
                             MirrorFileRecord);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ERROR: Failed to write $DATA attribute of $MFTMirr!\n");
    }

    // Cleanup
    ReleaseAttributeContext(MftDataContext);
    ReleaseAttributeContext(MirrDataContext);
    ExFreePoolWithTag(DataBuffer, TAG_NTFS);
    ExFreeToNPagedLookasideList(&Vcb->FileRecLookasideList, MirrorFileRecord);

    return Status;
}
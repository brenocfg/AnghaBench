#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  Directory; int /*<<< orphan*/  DeletePending; int /*<<< orphan*/  NumberOfLinks; int /*<<< orphan*/  EndOfFile; int /*<<< orphan*/  AllocationSize; } ;
struct TYPE_10__ {int /*<<< orphan*/  FileSize; int /*<<< orphan*/  AllocationSize; } ;
struct TYPE_11__ {int /*<<< orphan*/  LinkCount; TYPE_1__ RFCB; } ;
typedef  int* PULONG ;
typedef  TYPE_2__* PNTFS_FCB ;
typedef  TYPE_3__* PFILE_STANDARD_INFORMATION ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_STANDARD_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NtfsFCBIsDirectory (TYPE_2__*) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NTSTATUS
NtfsGetStandardInformation(PNTFS_FCB Fcb,
                           PDEVICE_OBJECT DeviceObject,
                           PFILE_STANDARD_INFORMATION StandardInfo,
                           PULONG BufferLength)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    DPRINT("NtfsGetStandardInformation(%p, %p, %p, %p)\n", Fcb, DeviceObject, StandardInfo, BufferLength);

    if (*BufferLength < sizeof(FILE_STANDARD_INFORMATION))
        return STATUS_BUFFER_TOO_SMALL;

    /* PRECONDITION */
    ASSERT(StandardInfo != NULL);
    ASSERT(Fcb != NULL);

    RtlZeroMemory(StandardInfo,
                  sizeof(FILE_STANDARD_INFORMATION));

    StandardInfo->AllocationSize = Fcb->RFCB.AllocationSize;
    StandardInfo->EndOfFile = Fcb->RFCB.FileSize;
    StandardInfo->NumberOfLinks = Fcb->LinkCount;
    StandardInfo->DeletePending = FALSE;
    StandardInfo->Directory = NtfsFCBIsDirectory(Fcb);

    *BufferLength -= sizeof(FILE_STANDARD_INFORMATION);

    return STATUS_SUCCESS;
}
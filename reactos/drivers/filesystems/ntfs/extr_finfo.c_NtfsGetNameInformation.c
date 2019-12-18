#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_8__ {int FileNameLength; int /*<<< orphan*/  FileName; } ;
struct TYPE_7__ {int /*<<< orphan*/  PathName; } ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_1__* PNTFS_FCB ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  TYPE_2__* PFILE_NAME_INFORMATION ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__*) ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_NAME_INFORMATION ; 
 int /*<<< orphan*/ * FileName ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 
 scalar_t__ min (int,scalar_t__) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NTSTATUS
NtfsGetNameInformation(PFILE_OBJECT FileObject,
                       PNTFS_FCB Fcb,
                       PDEVICE_OBJECT DeviceObject,
                       PFILE_NAME_INFORMATION NameInfo,
                       PULONG BufferLength)
{
    ULONG BytesToCopy;

    UNREFERENCED_PARAMETER(FileObject);
    UNREFERENCED_PARAMETER(DeviceObject);

    DPRINT("NtfsGetNameInformation(%p, %p, %p, %p, %p)\n", FileObject, Fcb, DeviceObject, NameInfo, BufferLength);

    ASSERT(NameInfo != NULL);
    ASSERT(Fcb != NULL);

    /* If buffer can't hold at least the file name length, bail out */
    if (*BufferLength < (ULONG)FIELD_OFFSET(FILE_NAME_INFORMATION, FileName[0]))
        return STATUS_BUFFER_TOO_SMALL;

    /* Save file name length, and as much file len, as buffer length allows */
    NameInfo->FileNameLength = wcslen(Fcb->PathName) * sizeof(WCHAR);

    /* Calculate amount of bytes to copy not to overflow the buffer */
    BytesToCopy = min(NameInfo->FileNameLength,
                      *BufferLength - FIELD_OFFSET(FILE_NAME_INFORMATION, FileName[0]));

    /* Fill in the bytes */
    RtlCopyMemory(NameInfo->FileName, Fcb->PathName, BytesToCopy);

    /* Check if we could write more but are not able to */
    if (*BufferLength < NameInfo->FileNameLength + (ULONG)FIELD_OFFSET(FILE_NAME_INFORMATION, FileName[0]))
    {
        /* Return number of bytes written */
        *BufferLength -= FIELD_OFFSET(FILE_NAME_INFORMATION, FileName[0]) + BytesToCopy;
        return STATUS_BUFFER_OVERFLOW;
    }

    /* We filled up as many bytes, as needed */
    *BufferLength -= (FIELD_OFFSET(FILE_NAME_INFORMATION, FileName[0]) + NameInfo->FileNameLength);

    return STATUS_SUCCESS;
}
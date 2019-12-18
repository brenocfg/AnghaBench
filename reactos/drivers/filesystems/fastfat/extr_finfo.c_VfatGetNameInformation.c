#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_8__ {scalar_t__ FileNameLength; int /*<<< orphan*/  FileName; } ;
struct TYPE_6__ {scalar_t__ Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_7__ {TYPE_1__ PathNameU; } ;
typedef  TYPE_2__* PVFATFCB ;
typedef  scalar_t__* PULONG ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  TYPE_3__* PFILE_NAME_INFORMATION ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_NAME_INFORMATION ; 
 int /*<<< orphan*/ * FileName ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static
NTSTATUS
VfatGetNameInformation(
    PFILE_OBJECT FileObject,
    PVFATFCB FCB,
    PDEVICE_EXTENSION DeviceExt,
    PFILE_NAME_INFORMATION NameInfo,
    PULONG BufferLength)
{
    ULONG BytesToCopy;

    UNREFERENCED_PARAMETER(FileObject);
    UNREFERENCED_PARAMETER(DeviceExt);

    ASSERT(NameInfo != NULL);
    ASSERT(FCB != NULL);

    /* If buffer can't hold at least the file name length, bail out */
    if (*BufferLength < (ULONG)FIELD_OFFSET(FILE_NAME_INFORMATION, FileName[0]))
        return STATUS_BUFFER_OVERFLOW;

    /* Save file name length, and as much file len, as buffer length allows */
    NameInfo->FileNameLength = FCB->PathNameU.Length;

    /* Calculate amount of bytes to copy not to overflow the buffer */
    BytesToCopy = min(FCB->PathNameU.Length,
                      *BufferLength - FIELD_OFFSET(FILE_NAME_INFORMATION, FileName[0]));

    /* Fill in the bytes */
    RtlCopyMemory(NameInfo->FileName, FCB->PathNameU.Buffer, BytesToCopy);

    /* Check if we could write more but are not able to */
    if (*BufferLength < FCB->PathNameU.Length + (ULONG)FIELD_OFFSET(FILE_NAME_INFORMATION, FileName[0]))
    {
        /* Return number of bytes written */
        *BufferLength -= FIELD_OFFSET(FILE_NAME_INFORMATION, FileName[0]) + BytesToCopy;
        return STATUS_BUFFER_OVERFLOW;
    }

    /* We filled up as many bytes, as needed */
    *BufferLength -= (FIELD_OFFSET(FILE_NAME_INFORMATION, FileName[0]) + FCB->PathNameU.Length);

    return STATUS_SUCCESS;
}
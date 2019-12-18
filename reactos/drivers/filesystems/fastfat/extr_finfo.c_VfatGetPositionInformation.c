#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_15__ {TYPE_2__ CurrentByteOffset; } ;
struct TYPE_12__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_14__ {TYPE_1__ CurrentByteOffset; } ;
typedef  TYPE_3__* PVFATFCB ;
typedef  int* PULONG ;
typedef  TYPE_4__* PFILE_POSITION_INFORMATION ;
typedef  TYPE_3__* PFILE_OBJECT ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_POSITION_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (TYPE_3__*) ; 

__attribute__((used)) static
NTSTATUS
VfatGetPositionInformation(
    PFILE_OBJECT FileObject,
    PVFATFCB FCB,
    PDEVICE_EXTENSION DeviceExt,
    PFILE_POSITION_INFORMATION PositionInfo,
    PULONG BufferLength)
{
    UNREFERENCED_PARAMETER(FileObject);
    UNREFERENCED_PARAMETER(FCB);
    UNREFERENCED_PARAMETER(DeviceExt);

    DPRINT("VfatGetPositionInformation()\n");

    if (*BufferLength < sizeof(FILE_POSITION_INFORMATION))
        return STATUS_BUFFER_OVERFLOW;

    PositionInfo->CurrentByteOffset.QuadPart =
        FileObject->CurrentByteOffset.QuadPart;

    DPRINT("Getting position %I64x\n",
           PositionInfo->CurrentByteOffset.QuadPart);

    *BufferLength -= sizeof(FILE_POSITION_INFORMATION);
    return STATUS_SUCCESS;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_12__ {TYPE_1__ CurrentByteOffset; } ;
struct TYPE_10__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_11__ {TYPE_2__ CurrentByteOffset; } ;
typedef  int* PULONG ;
typedef  TYPE_3__* PFILE_POSITION_INFORMATION ;
typedef  TYPE_4__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_POSITION_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_4__*,TYPE_3__*,int*) ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static
NTSTATUS
NtfsGetPositionInformation(PFILE_OBJECT FileObject,
                           PFILE_POSITION_INFORMATION PositionInfo,
                           PULONG BufferLength)
{
    DPRINT1("NtfsGetPositionInformation(%p, %p, %p)\n", FileObject, PositionInfo, BufferLength);

    if (*BufferLength < sizeof(FILE_POSITION_INFORMATION))
        return STATUS_BUFFER_TOO_SMALL;

    PositionInfo->CurrentByteOffset.QuadPart = FileObject->CurrentByteOffset.QuadPart;

    DPRINT("Getting position %I64x\n",
           PositionInfo->CurrentByteOffset.QuadPart);

    *BufferLength -= sizeof(FILE_POSITION_INFORMATION);

    return STATUS_SUCCESS;
}
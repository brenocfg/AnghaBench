#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_12__ {TYPE_2__ CurrentByteOffset; } ;
struct TYPE_8__ {TYPE_4__* LowPart; } ;
struct TYPE_10__ {int /*<<< orphan*/  QuadPart; TYPE_1__ u; } ;
struct TYPE_11__ {TYPE_3__ CurrentByteOffset; } ;
typedef  TYPE_4__* PFILE_POSITION_INFORMATION ;
typedef  TYPE_5__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static
NTSTATUS
VfatSetPositionInformation(
    PFILE_OBJECT FileObject,
    PFILE_POSITION_INFORMATION PositionInfo)
{
    DPRINT("FsdSetPositionInformation()\n");

    DPRINT("PositionInfo %p\n", PositionInfo);
    DPRINT("Setting position %u\n", PositionInfo->CurrentByteOffset.u.LowPart);

    FileObject->CurrentByteOffset.QuadPart =
        PositionInfo->CurrentByteOffset.QuadPart;

    return STATUS_SUCCESS;
}
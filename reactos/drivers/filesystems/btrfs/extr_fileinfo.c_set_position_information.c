#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_13__ {TYPE_2__ CurrentByteOffset; } ;
struct TYPE_12__ {TYPE_2__ CurrentByteOffset; } ;
struct TYPE_9__ {scalar_t__ SystemBuffer; } ;
struct TYPE_11__ {TYPE_1__ AssociatedIrp; } ;
typedef  TYPE_3__* PIRP ;
typedef  TYPE_4__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_5__ FILE_POSITION_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS set_position_information(PFILE_OBJECT FileObject, PIRP Irp) {
    FILE_POSITION_INFORMATION* fpi = (FILE_POSITION_INFORMATION*)Irp->AssociatedIrp.SystemBuffer;

    TRACE("setting the position on %p to %I64x\n", FileObject, fpi->CurrentByteOffset.QuadPart);

    // FIXME - make sure aligned for FO_NO_INTERMEDIATE_BUFFERING

    FileObject->CurrentByteOffset = fpi->CurrentByteOffset;

    return STATUS_SUCCESS;
}
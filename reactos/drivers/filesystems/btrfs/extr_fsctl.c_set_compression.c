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
typedef  scalar_t__ USHORT ;
struct TYPE_9__ {int InputBufferLength; } ;
struct TYPE_10__ {TYPE_1__ FileSystemControl; } ;
struct TYPE_13__ {TYPE_2__ Parameters; } ;
struct TYPE_11__ {scalar_t__* SystemBuffer; } ;
struct TYPE_12__ {TYPE_3__ AssociatedIrp; } ;
typedef  TYPE_4__* PIRP ;
typedef  TYPE_5__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ COMPRESSION_FORMAT_NONE ; 
 TYPE_5__* IoGetCurrentIrpStackLocation (TYPE_4__*) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static NTSTATUS set_compression(PIRP Irp) {
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    USHORT* compression;

    TRACE("FSCTL_SET_COMPRESSION\n");

    if (IrpSp->Parameters.FileSystemControl.InputBufferLength < sizeof(USHORT))
        return STATUS_INVALID_PARAMETER;

    compression = Irp->AssociatedIrp.SystemBuffer;

    if (*compression != COMPRESSION_FORMAT_NONE)
        return STATUS_INVALID_PARAMETER;

    return STATUS_SUCCESS;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_19__ {int NumberProcessors; } ;
struct TYPE_18__ {int /*<<< orphan*/  Statistics; } ;
struct TYPE_17__ {TYPE_5__* Irp; TYPE_2__* Stack; TYPE_8__* DeviceExt; } ;
struct TYPE_16__ {int OutputBufferLength; } ;
struct TYPE_14__ {int Information; } ;
struct TYPE_13__ {int /*<<< orphan*/ * SystemBuffer; } ;
struct TYPE_15__ {TYPE_4__ IoStatus; TYPE_3__ AssociatedIrp; } ;
struct TYPE_11__ {TYPE_6__ FileSystemControl; } ;
struct TYPE_12__ {TYPE_1__ Parameters; } ;
typedef  int /*<<< orphan*/  STATISTICS ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_7__* PVFAT_IRP_CONTEXT ;
typedef  TYPE_8__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILESYSTEM_STATISTICS ;

/* Variables and functions */
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_INVALID_USER_BUFFER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 TYPE_9__* VfatGlobalData ; 

__attribute__((used)) static
NTSTATUS
VfatGetStatistics(
    PVFAT_IRP_CONTEXT IrpContext)
{
    PVOID Buffer;
    ULONG Length;
    NTSTATUS Status;
    PDEVICE_EXTENSION DeviceExt;

    DeviceExt = IrpContext->DeviceExt;
    Length = IrpContext->Stack->Parameters.FileSystemControl.OutputBufferLength;
    Buffer = IrpContext->Irp->AssociatedIrp.SystemBuffer;

    if (Length < sizeof(FILESYSTEM_STATISTICS))
    {
        return STATUS_BUFFER_TOO_SMALL;
    }

    if (Buffer == NULL)
    {
        return STATUS_INVALID_USER_BUFFER;
    }

    if (Length >= sizeof(STATISTICS) * VfatGlobalData->NumberProcessors)
    {
        Length = sizeof(STATISTICS) * VfatGlobalData->NumberProcessors;
        Status = STATUS_SUCCESS;
    }
    else
    {
        Status = STATUS_BUFFER_OVERFLOW;
    }

    RtlCopyMemory(Buffer, DeviceExt->Statistics, Length);
    IrpContext->Irp->IoStatus.Information = Length;

    return Status;
}
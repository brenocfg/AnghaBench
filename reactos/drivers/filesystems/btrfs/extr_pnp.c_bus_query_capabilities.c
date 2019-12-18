#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int UniqueID; int SilentInstall; } ;
struct TYPE_6__ {TYPE_4__* Capabilities; } ;
struct TYPE_7__ {TYPE_1__ DeviceCapabilities; } ;
struct TYPE_8__ {TYPE_2__ Parameters; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_3__* PIO_STACK_LOCATION ;
typedef  TYPE_4__* PDEVICE_CAPABILITIES ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 TYPE_3__* IoGetCurrentIrpStackLocation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static NTSTATUS bus_query_capabilities(PIRP Irp) {
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    PDEVICE_CAPABILITIES dc = IrpSp->Parameters.DeviceCapabilities.Capabilities;

    dc->UniqueID = true;
    dc->SilentInstall = true;

    return STATUS_SUCCESS;
}
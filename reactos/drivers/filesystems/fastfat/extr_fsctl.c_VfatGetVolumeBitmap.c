#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PVFAT_IRP_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INVALID_DEVICE_REQUEST ; 

__attribute__((used)) static
NTSTATUS
VfatGetVolumeBitmap(
    PVFAT_IRP_CONTEXT IrpContext)
{
    DPRINT("VfatGetVolumeBitmap (IrpContext %p)\n", IrpContext);
    return STATUS_INVALID_DEVICE_REQUEST;
}
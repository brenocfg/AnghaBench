#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/  IsFDO; } ;
struct TYPE_5__ {int /*<<< orphan*/  NoPendingRequests; int /*<<< orphan*/  IrpListHead; int /*<<< orphan*/  IrpListLock; TYPE_1__ Common; } ;
typedef  TYPE_2__* PFDO_DEVICE_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeInitializeSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  TRUE ; 

VOID
USBSTOR_QueueInitialize(
    PFDO_DEVICE_EXTENSION FDODeviceExtension)
{
    ASSERT(FDODeviceExtension->Common.IsFDO);
    KeInitializeSpinLock(&FDODeviceExtension->IrpListLock);
    InitializeListHead(&FDODeviceExtension->IrpListHead);
    KeInitializeEvent(&FDODeviceExtension->NoPendingRequests, NotificationEvent, TRUE);
}
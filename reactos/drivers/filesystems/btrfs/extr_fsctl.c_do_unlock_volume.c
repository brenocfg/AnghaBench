#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  event; } ;
struct TYPE_7__ {int locked; TYPE_2__ balance; scalar_t__ lock_paused_balance; int /*<<< orphan*/ * locked_fileobj; TYPE_1__* Vpb; } ;
typedef  TYPE_3__ device_extension ;
struct TYPE_5__ {int /*<<< orphan*/  Flags; } ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  IoAcquireVpbSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoReleaseVpbSpinLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VPB_LOCKED ; 

void do_unlock_volume(device_extension* Vcb) {
    KIRQL irql;

    IoAcquireVpbSpinLock(&irql);

    Vcb->locked = false;
    Vcb->Vpb->Flags &= ~VPB_LOCKED;
    Vcb->locked_fileobj = NULL;

    IoReleaseVpbSpinLock(irql);

    if (Vcb->lock_paused_balance)
        KeSetEvent(&Vcb->balance.event, 0, false);
}
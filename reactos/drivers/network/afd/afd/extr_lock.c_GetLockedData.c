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
struct TYPE_5__ {int /*<<< orphan*/ * DriverContext; } ;
struct TYPE_6__ {TYPE_1__ Overlay; } ;
struct TYPE_7__ {TYPE_2__ Tail; int /*<<< orphan*/  MdlAddress; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_3__* PIRP ;
typedef  int /*<<< orphan*/  PIO_STACK_LOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 

PVOID GetLockedData(PIRP Irp, PIO_STACK_LOCATION IrpSp)
{
    ASSERT(Irp->MdlAddress);
    ASSERT(Irp->Tail.Overlay.DriverContext[0]);

    UNREFERENCED_PARAMETER(IrpSp);

    return Irp->Tail.Overlay.DriverContext[0];
}
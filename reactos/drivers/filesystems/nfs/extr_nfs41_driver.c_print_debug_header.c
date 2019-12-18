#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  SharedDelete; int /*<<< orphan*/  SharedWrite; int /*<<< orphan*/  SharedRead; int /*<<< orphan*/  DeleteAccess; int /*<<< orphan*/  WriteAccess; int /*<<< orphan*/  ReadAccess; int /*<<< orphan*/  FileName; } ;
struct TYPE_8__ {TYPE_5__* FileObject; } ;
struct TYPE_7__ {scalar_t__ CurrentIrp; TYPE_2__* CurrentIrpSp; } ;
typedef  TYPE_1__* PRX_CONTEXT ;
typedef  TYPE_2__* PIO_STACK_LOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  DbgP (char*,...) ; 
 int /*<<< orphan*/  print_file_object (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  print_fo_all (int,TYPE_1__*) ; 
 int /*<<< orphan*/  print_irp_flags (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  print_irps_flags (int /*<<< orphan*/ ,TYPE_2__*) ; 

void print_debug_header(
    PRX_CONTEXT RxContext)
{

    PIO_STACK_LOCATION IrpSp = RxContext->CurrentIrpSp;

    if (IrpSp) {
        DbgP("FileOject %p name %wZ access r=%d,w=%d,d=%d share r=%d,w=%d,d=%d\n",
            IrpSp->FileObject, &IrpSp->FileObject->FileName,
            IrpSp->FileObject->ReadAccess, IrpSp->FileObject->WriteAccess,
            IrpSp->FileObject->DeleteAccess, IrpSp->FileObject->SharedRead,
            IrpSp->FileObject->SharedWrite, IrpSp->FileObject->SharedDelete);
        print_file_object(0, IrpSp->FileObject);
        print_irps_flags(0, RxContext->CurrentIrpSp);
    } else
        DbgP("Couldn't print FileObject IrpSp is NULL\n");

    print_fo_all(1, RxContext);
    if (RxContext->CurrentIrp)
        print_irp_flags(0, RxContext->CurrentIrp);
}
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
typedef  scalar_t__ ULONG ;
struct TYPE_9__ {TYPE_3__* Srb; } ;
struct TYPE_10__ {TYPE_1__ Scsi; } ;
struct TYPE_13__ {TYPE_2__ Parameters; } ;
struct TYPE_12__ {int /*<<< orphan*/ * MdlAddress; } ;
struct TYPE_11__ {int SrbFlags; scalar_t__ DataTransferLength; scalar_t__ DataBuffer; } ;
typedef  TYPE_3__* PSCSI_REQUEST_BLOCK ;
typedef  TYPE_4__* PIRP ;
typedef  TYPE_5__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_5__* IoGetCurrentIrpStackLocation (TYPE_4__*) ; 
 int SRB_FLAGS_DATA_IN ; 
 int SRB_FLAGS_DATA_OUT ; 
 int SRB_FLAGS_UNSPECIFIED_DIRECTION ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ USBSTOR_DEFAULT_MAX_TRANSFER_LENGTH ; 

__attribute__((used)) static
BOOLEAN
IsRequestValid(PIRP Irp)
{
    ULONG TransferLength;
    PIO_STACK_LOCATION IoStack;
    PSCSI_REQUEST_BLOCK Srb;

    IoStack = IoGetCurrentIrpStackLocation(Irp);
    Srb = IoStack->Parameters.Scsi.Srb;

    if (Srb->SrbFlags & (SRB_FLAGS_DATA_IN | SRB_FLAGS_DATA_OUT))
    {
        if ((Srb->SrbFlags & SRB_FLAGS_UNSPECIFIED_DIRECTION) == SRB_FLAGS_UNSPECIFIED_DIRECTION)
        {
            DPRINT1("IsRequestValid: Invalid Srb. Srb->SrbFlags - %X\n", Srb->SrbFlags);
            return FALSE;
        }

        TransferLength = Srb->DataTransferLength;

        if (Irp->MdlAddress == NULL)
        {
            DPRINT1("IsRequestValid: Invalid Srb. Irp->MdlAddress == NULL\n");
            return FALSE;
        }

        if (TransferLength == 0)
        {
            DPRINT1("IsRequestValid: Invalid Srb. TransferLength == 0\n");
            return FALSE;
        }

        if (TransferLength > USBSTOR_DEFAULT_MAX_TRANSFER_LENGTH)
        {
            DPRINT1("IsRequestValid: Invalid Srb. TransferLength > 0x10000\n");
            return FALSE;
        }
    }
    else
    {
        if (Srb->DataTransferLength)
        {
            DPRINT1("IsRequestValid: Invalid Srb. Srb->DataTransferLength != 0\n");
            return FALSE;
        }

        if (Srb->DataBuffer)
        {
            DPRINT1("IsRequestValid: Invalid Srb. Srb->DataBuffer != NULL\n");
            return FALSE;
        }

        if (Irp->MdlAddress)
        {
            DPRINT1("IsRequestValid: Invalid Srb. Irp->MdlAddress != NULL\n");
            return FALSE;
        }
    }

    return TRUE;
}
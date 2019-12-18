#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_19__ {int i_size; } ;
struct TYPE_18__ {scalar_t__ MajorFunction; } ;
struct TYPE_17__ {TYPE_6__ Inode; } ;
struct TYPE_16__ {int QuadPart; } ;
typedef  TYPE_1__* PLARGE_INTEGER ;
typedef  int /*<<< orphan*/  PEXT2_VCB ;
typedef  TYPE_2__* PEXT2_MCB ;
typedef  TYPE_3__* PEXT2_IRP_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONGLONG ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int BLOCK_BITS ; 
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  Ext2ExpandExtent (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  Ext2ExpandIndirect (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,scalar_t__,TYPE_1__*) ; 
 scalar_t__ INODE_HAS_EXTENT (TYPE_6__*) ; 
 scalar_t__ IRP_MJ_WRITE ; 
 scalar_t__ IsMcbDirectory (TYPE_2__*) ; 
 scalar_t__ IsMcbSpecialFile (TYPE_2__*) ; 
 int /*<<< orphan*/  STATUS_INVALID_DEVICE_REQUEST ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int TRUE ; 

NTSTATUS
Ext2ExpandFile(
    PEXT2_IRP_CONTEXT IrpContext,
    PEXT2_VCB         Vcb,
    PEXT2_MCB         Mcb,
    PLARGE_INTEGER    Size
)
{
    NTSTATUS status = STATUS_SUCCESS;
    ULONG    Start = 0;
    ULONG    End = 0;

    Start = (ULONG)((Mcb->Inode.i_size + BLOCK_SIZE - 1) >> BLOCK_BITS);
    End = (ULONG)((Size->QuadPart + BLOCK_SIZE - 1) >> BLOCK_BITS);

    /* it's a truncate operation, not expanding */
    if (Start >= End) {
        Size->QuadPart = ((LONGLONG) Start) << BLOCK_BITS;
        return STATUS_SUCCESS;
    }

	/* ignore special files */
	if (IsMcbSpecialFile(Mcb)) {
        return STATUS_INVALID_DEVICE_REQUEST;
    }

	/* expandind file extents */ 
    if (INODE_HAS_EXTENT(&Mcb->Inode)) {

        status = Ext2ExpandExtent(IrpContext, Vcb, Mcb, Start, End, Size);

    } else {

        BOOLEAN do_expand;

#if EXT2_PRE_ALLOCATION_SUPPORT
        do_expand = TRUE;
#else
        do_expand = (IrpContext->MajorFunction == IRP_MJ_WRITE) ||
                    IsMcbDirectory(Mcb);
#endif
        if (!do_expand)
            goto errorout;

        status = Ext2ExpandIndirect(IrpContext, Vcb, Mcb, Start, End, Size);
    }

errorout:
    return status;
}
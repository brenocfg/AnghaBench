#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_14__ {scalar_t__* i_block; } ;
struct TYPE_13__ {TYPE_5__ Inode; } ;
struct TYPE_12__ {scalar_t__ max_data_blocks; scalar_t__* max_blocks_per_layer; } ;
struct TYPE_11__ {int QuadPart; } ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  TYPE_1__* PLARGE_INTEGER ;
typedef  TYPE_2__* PEXT2_VCB ;
typedef  TYPE_3__* PEXT2_MCB ;
typedef  int /*<<< orphan*/  PEXT2_IRP_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONGLONG ;

/* Variables and functions */
 int BLOCK_BITS ; 
 scalar_t__ EXT2_BLOCK_TYPES ; 
 scalar_t__ EXT2_NDIR_BLOCKS ; 
 int /*<<< orphan*/  Ext2ExpandBlock (int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  Ext2SaveInode (int /*<<< orphan*/ ,TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
Ext2ExpandIndirect(
    PEXT2_IRP_CONTEXT IrpContext,
    PEXT2_VCB         Vcb,
    PEXT2_MCB         Mcb,
    ULONG             Start,
    ULONG             End,
    PLARGE_INTEGER    Size
)
{
    NTSTATUS Status = STATUS_SUCCESS;

    ULONG    Layer = 0;
    ULONG    Extra = 0;
    ULONG    Hint = 0;
    ULONG    Slot = 0;
    ULONG    Base = 0;

    Extra = End - Start;

	/* exceeds the biggest file size (indirect) */
    if (End > Vcb->max_data_blocks) {
        return STATUS_INVALID_PARAMETER;
    }

    for (Layer = 0; Layer < EXT2_BLOCK_TYPES && Extra; Layer++) {

        if (Start >= Vcb->max_blocks_per_layer[Layer]) {

            Base  += Vcb->max_blocks_per_layer[Layer];
            Start -= Vcb->max_blocks_per_layer[Layer];

        } else {

            /* get the slot in i_block array */
            if (Layer == 0) {
                Base = Slot = Start;
            } else {
                Slot = Layer + EXT2_NDIR_BLOCKS - 1;
            }

            /* set block hint to avoid fragments */
            if (Hint == 0) {
                if (Mcb->Inode.i_block[Slot] != 0) {
                    Hint = Mcb->Inode.i_block[Slot];
                } else if (Slot > 1) {
                    Hint = Mcb->Inode.i_block[Slot-1];
                }
            }

            /* now expand this slot */
            Status = Ext2ExpandBlock(
                         IrpContext,
                         Vcb,
                         Mcb,
                         Base,
                         Layer,
                         Start,
                         (Layer == 0) ? (Vcb->max_blocks_per_layer[Layer] - Start) : 1,
                         (PULONG)&Mcb->Inode.i_block[Slot],
                         &Hint,
                         &Extra
                     );
            if (!NT_SUCCESS(Status)) {
                break;
            }

            Start = 0;
            if (Layer == 0) {
                Base = 0;
            }
            Base += Vcb->max_blocks_per_layer[Layer];
        }
    }

    Size->QuadPart = ((LONGLONG)(End - Extra)) << BLOCK_BITS;

    /* save inode whatever it succeeds to expand or not */
    Ext2SaveInode(IrpContext, Vcb, &Mcb->Inode);

    return Status;
}
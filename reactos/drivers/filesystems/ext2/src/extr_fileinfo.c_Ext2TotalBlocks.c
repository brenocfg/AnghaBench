#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_6__ {int* max_blocks_per_layer; } ;
struct TYPE_5__ {int QuadPart; } ;
typedef  int* PULONG ;
typedef  TYPE_1__* PLARGE_INTEGER ;
typedef  TYPE_2__* PEXT2_VCB ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BLOCK_BITS ; 
 int BLOCK_SIZE ; 
 int EXT2_NDIR_BLOCKS ; 

ULONG
Ext2TotalBlocks(
    PEXT2_VCB         Vcb,
    PLARGE_INTEGER    Size,
    PULONG            pMeta
)
{
    ULONG Blocks, Meta =0, Remain;

    Blocks = (ULONG)((Size->QuadPart + BLOCK_SIZE - 1) >> BLOCK_BITS);
    if (Blocks <= EXT2_NDIR_BLOCKS)
        goto errorout;
    Blocks -= EXT2_NDIR_BLOCKS;

    Meta += 1;
    if (Blocks <= Vcb->max_blocks_per_layer[1]) {
        goto errorout;
    }
    Blocks -= Vcb->max_blocks_per_layer[1];

level2:

    if (Blocks <= Vcb->max_blocks_per_layer[2]) {
        Meta += 1 + ((Blocks + BLOCK_SIZE/4 - 1) >> (BLOCK_BITS - 2));
        goto errorout;
    }
    Meta += 1 + BLOCK_SIZE/4;
    Blocks -= Vcb->max_blocks_per_layer[2];

    if (Blocks > Vcb->max_blocks_per_layer[3]) {
        Blocks  = Vcb->max_blocks_per_layer[3];
    }

    ASSERT(Vcb->max_blocks_per_layer[2]);
    Remain = Blocks % Vcb->max_blocks_per_layer[2];
    Blocks = Blocks / Vcb->max_blocks_per_layer[2];
    Meta += 1 + Blocks * (1 + BLOCK_SIZE/4);
    if (Remain) {
        Blocks = Remain;
        goto level2;
    }

errorout:

    if (pMeta)
        *pMeta = Meta;
    Blocks = (ULONG)((Size->QuadPart + BLOCK_SIZE - 1) >> BLOCK_BITS);
    return (Blocks + Meta);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct buffer_head {int b_data; int b_size; scalar_t__ b_blocknr; struct block_device* b_bdev; } ;
struct block_device {TYPE_2__* bd_priv; } ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_11__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_10__ {int QuadPart; } ;
struct TYPE_8__ {scalar_t__ Type; } ;
struct TYPE_9__ {TYPE_6__* Volume; TYPE_1__ Identifier; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PEXT2_VCB ;
typedef  int /*<<< orphan*/  PBCB ;
typedef  int LONGLONG ;
typedef  TYPE_3__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BLOCK_BITS ; 
 int /*<<< orphan*/  BLOCK_SIZE ; 
 scalar_t__ CcPreparePinWrite (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CcSetDirtyPinnedData (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CcUnpinData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgBreak () ; 
 scalar_t__ EXT2VCB ; 
 int /*<<< orphan*/  Ext2AddBlockExtent (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FO_FILE_MODIFIED ; 
 scalar_t__ IsVcbReadOnly (TYPE_2__*) ; 
 int /*<<< orphan*/  PIN_WAIT ; 
 int /*<<< orphan*/  SetFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WRITE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

int submit_bh_mdl(int rw, struct buffer_head *bh)
{
    struct block_device *bdev = bh->b_bdev;
    PEXT2_VCB            Vcb  = bdev->bd_priv;
    PBCB                 Bcb;
    PVOID                Buffer;
    LARGE_INTEGER        Offset;

    ASSERT(Vcb->Identifier.Type == EXT2VCB);
    ASSERT(bh->b_data);

    if (rw == WRITE) {

        if (IsVcbReadOnly(Vcb)) {
            goto errorout;
        }

        SetFlag(Vcb->Volume->Flags, FO_FILE_MODIFIED);
        Offset.QuadPart = ((LONGLONG)bh->b_blocknr) << BLOCK_BITS;

        /* PIN_EXCLUSIVE disabled, likely to deadlock with volume operations */
        if (CcPreparePinWrite(
                    Vcb->Volume,
                    &Offset,
                    BLOCK_SIZE,
                    FALSE,
                    PIN_WAIT /* | PIN_EXCLUSIVE */,
                    &Bcb,
                    &Buffer )) {
#if 0
            if (memcmp(Buffer, bh->b_data, BLOCK_SIZE) != 0) {
                DbgBreak();
            }
            memmove(Buffer, bh->b_data, BLOCK_SIZE);
#endif
            CcSetDirtyPinnedData(Bcb, NULL);
            Ext2AddBlockExtent( Vcb, NULL,
                                (ULONG)bh->b_blocknr,
                                (ULONG)bh->b_blocknr,
                                (bh->b_size >> BLOCK_BITS));
            CcUnpinData(Bcb);
        } else {

            Ext2AddBlockExtent( Vcb, NULL,
                                (ULONG)bh->b_blocknr,
                                (ULONG)bh->b_blocknr,
                                (bh->b_size >> BLOCK_BITS));
        }

    } else {
    }

errorout:

    unlock_buffer(bh);
    put_bh(bh);
    return 0;
}
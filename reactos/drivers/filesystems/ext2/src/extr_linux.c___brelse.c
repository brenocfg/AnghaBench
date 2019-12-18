#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct buffer_head {int /*<<< orphan*/  b_data; int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_link; int /*<<< orphan*/  b_ts_drop; int /*<<< orphan*/  b_count; struct block_device* b_bdev; } ;
struct block_device {int /*<<< orphan*/  bd_bh_lock; int /*<<< orphan*/  bd_priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  Wait; } ;
struct TYPE_12__ {TYPE_3__ bhReaper; } ;
struct TYPE_11__ {int /*<<< orphan*/  bh_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  bd_bh_notify; int /*<<< orphan*/  bd_bh_free; } ;
struct TYPE_7__ {scalar_t__ Type; } ;
struct TYPE_10__ {TYPE_2__ bd; TYPE_1__ Identifier; } ;
typedef  TYPE_4__* PEXT2_VCB ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DL_BH ; 
 scalar_t__ EXT2VCB ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 TYPE_6__* Ext2Global ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeClearEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeQuerySystemTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WRITE ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 TYPE_5__ g_jbh ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 

void __brelse(struct buffer_head *bh)
{
    struct block_device *bdev = bh->b_bdev;
    PEXT2_VCB Vcb = (PEXT2_VCB)bdev->bd_priv;

    ASSERT(Vcb->Identifier.Type == EXT2VCB);

    /* write data in case it's dirty */
    while (buffer_dirty(bh)) {
        ll_rw_block(WRITE, 1, &bh);
    }

    ExAcquireResourceExclusiveLite(&bdev->bd_bh_lock, TRUE);
    if (atomic_dec_and_test(&bh->b_count)) {
        ASSERT(0 == atomic_read(&bh->b_count));
    } else {
        ExReleaseResourceLite(&bdev->bd_bh_lock);
        return;
    }
    KeQuerySystemTime(&bh->b_ts_drop);
#ifdef __REACTOS__
    if (!IsListEmpty(&bh->b_link))
#endif
    RemoveEntryList(&bh->b_link);
    InsertTailList(&Vcb->bd.bd_bh_free, &bh->b_link);
    KeClearEvent(&Vcb->bd.bd_bh_notify);
    ExReleaseResourceLite(&bdev->bd_bh_lock);
    KeSetEvent(&Ext2Global->bhReaper.Wait, 0, FALSE);

    DEBUG(DL_BH, ("brelse: cnt=%u size=%u blk=%10.10xh bh=%p ptr=%p\n",
                  atomic_read(&g_jbh.bh_count) - 1, bh->b_size,
                  bh->b_blocknr, bh, bh->b_data ));
}
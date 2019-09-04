#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct TYPE_4__ {int mem_blocks; int /*<<< orphan*/  mem_block_size; } ;
struct ar9170 {int /*<<< orphan*/  mem_lock; int /*<<< orphan*/  mem_bitmap; int /*<<< orphan*/  mem_free_blocks; TYPE_2__ fw; } ;
struct TYPE_3__ {int cookie; } ;
struct _carl9170_tx_superframe {TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void carl9170_release_dev_space(struct ar9170 *ar, struct sk_buff *skb)
{
	struct _carl9170_tx_superframe *super = (void *) skb->data;
	int cookie;

	/* make a local copy of the cookie */
	cookie = super->s.cookie;
	/* invalidate cookie */
	super->s.cookie = 0;

	/*
	 * Do a out-of-bounds check on the cookie:
	 *
	 *  * cookie "0" is reserved and won't be assigned to any
	 *    out-going frame. Internally however, it is used to
	 *    mark no longer/un-accounted frames and serves as a
	 *    cheap way of preventing frames from being freed
	 *    twice by _accident_. NB: There is a tiny race...
	 *
	 *  * obviously, cookie number is limited by the amount
	 *    of available memory blocks, so the number can
	 *    never execeed the mem_blocks count.
	 */
	if (unlikely(WARN_ON_ONCE(cookie == 0) ||
	    WARN_ON_ONCE(cookie > ar->fw.mem_blocks)))
		return;

	atomic_add(DIV_ROUND_UP(skb->len, ar->fw.mem_block_size),
		   &ar->mem_free_blocks);

	spin_lock_bh(&ar->mem_lock);
	bitmap_release_region(ar->mem_bitmap, cookie - 1, 0);
	spin_unlock_bh(&ar->mem_lock);
}
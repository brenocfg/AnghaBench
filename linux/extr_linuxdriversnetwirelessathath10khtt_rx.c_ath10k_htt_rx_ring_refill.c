#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ fill_cnt; scalar_t__ fill_level; } ;
struct ath10k_htt {TYPE_1__ rx_ring; } ;
struct ath10k {struct ath10k_htt htt; } ;

/* Variables and functions */
 int ath10k_htt_rx_ring_fill_n (struct ath10k_htt*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_htt_rx_ring_free (struct ath10k_htt*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ath10k_htt_rx_ring_refill(struct ath10k *ar)
{
	struct ath10k_htt *htt = &ar->htt;
	int ret;

	spin_lock_bh(&htt->rx_ring.lock);
	ret = ath10k_htt_rx_ring_fill_n(htt, (htt->rx_ring.fill_level -
					      htt->rx_ring.fill_cnt));

	if (ret)
		ath10k_htt_rx_ring_free(htt);

	spin_unlock_bh(&htt->rx_ring.lock);

	return ret;
}
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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct ath10k_htt {TYPE_1__ rx_ring; } ;

/* Variables and functions */
 int __ath10k_htt_rx_ring_fill_n (struct ath10k_htt*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_htt_rx_ring_fill_n(struct ath10k_htt *htt, int num)
{
	lockdep_assert_held(&htt->rx_ring.lock);
	return __ath10k_htt_rx_ring_fill_n(htt, num);
}
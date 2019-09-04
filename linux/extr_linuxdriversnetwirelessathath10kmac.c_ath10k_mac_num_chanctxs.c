#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ath10k {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_mac_num_chanctxs_iter ; 
 int /*<<< orphan*/  ieee80211_iter_chan_contexts_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ath10k_mac_num_chanctxs(struct ath10k *ar)
{
	int num = 0;

	ieee80211_iter_chan_contexts_atomic(ar->hw,
					    ath10k_mac_num_chanctxs_iter,
					    &num);

	return num;
}
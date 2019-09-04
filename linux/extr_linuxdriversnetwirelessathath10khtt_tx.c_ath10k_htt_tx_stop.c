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
struct ath10k_htt {int /*<<< orphan*/  pending_tx; int /*<<< orphan*/  ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_htt_tx_clean_up_pending ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath10k_htt_tx_stop(struct ath10k_htt *htt)
{
	idr_for_each(&htt->pending_tx, ath10k_htt_tx_clean_up_pending, htt->ar);
	idr_destroy(&htt->pending_tx);
}
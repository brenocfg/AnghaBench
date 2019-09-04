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
struct ath10k_htt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_htt_tx_destroy (struct ath10k_htt*) ; 
 int /*<<< orphan*/  ath10k_htt_tx_stop (struct ath10k_htt*) ; 

void ath10k_htt_tx_free(struct ath10k_htt *htt)
{
	ath10k_htt_tx_stop(htt);
	ath10k_htt_tx_destroy(htt);
}
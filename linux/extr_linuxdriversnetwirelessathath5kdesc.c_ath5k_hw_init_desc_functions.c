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
struct ath5k_hw {scalar_t__ ah_version; int /*<<< orphan*/  ah_proc_rx_desc; int /*<<< orphan*/  ah_proc_tx_desc; int /*<<< orphan*/  ah_setup_tx_desc; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5211 ; 
 scalar_t__ AR5K_AR5212 ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  ath5k_hw_proc_2word_tx_status ; 
 int /*<<< orphan*/  ath5k_hw_proc_4word_tx_status ; 
 int /*<<< orphan*/  ath5k_hw_proc_5210_rx_status ; 
 int /*<<< orphan*/  ath5k_hw_proc_5212_rx_status ; 
 int /*<<< orphan*/  ath5k_hw_setup_2word_tx_desc ; 
 int /*<<< orphan*/  ath5k_hw_setup_4word_tx_desc ; 

int
ath5k_hw_init_desc_functions(struct ath5k_hw *ah)
{
	if (ah->ah_version == AR5K_AR5212) {
		ah->ah_setup_tx_desc = ath5k_hw_setup_4word_tx_desc;
		ah->ah_proc_tx_desc = ath5k_hw_proc_4word_tx_status;
		ah->ah_proc_rx_desc = ath5k_hw_proc_5212_rx_status;
	} else if (ah->ah_version <= AR5K_AR5211) {
		ah->ah_setup_tx_desc = ath5k_hw_setup_2word_tx_desc;
		ah->ah_proc_tx_desc = ath5k_hw_proc_2word_tx_status;
		ah->ah_proc_rx_desc = ath5k_hw_proc_5210_rx_status;
	} else
		return -ENOTSUPP;
	return 0;
}
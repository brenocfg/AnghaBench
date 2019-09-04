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
struct ath5k_txq_info {int /*<<< orphan*/  tqi_flags; int /*<<< orphan*/  tqi_cw_max; int /*<<< orphan*/  tqi_cw_min; int /*<<< orphan*/  tqi_aifs; } ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_TUNE_AIFS ; 
 int /*<<< orphan*/  AR5K_TUNE_CWMAX ; 
 int /*<<< orphan*/  AR5K_TUNE_CWMIN ; 
 int /*<<< orphan*/  AR5K_TXQ_FLAG_TXDESCINT_ENABLE ; 
 int /*<<< orphan*/  AR5K_TX_QUEUE_BEACON ; 
 int ath5k_hw_setup_tx_queue (struct ath5k_hw*,int /*<<< orphan*/ ,struct ath5k_txq_info*) ; 

__attribute__((used)) static int
ath5k_beaconq_setup(struct ath5k_hw *ah)
{
	struct ath5k_txq_info qi = {
		/* XXX: default values not correct for B and XR channels,
		 * but who cares? */
		.tqi_aifs = AR5K_TUNE_AIFS,
		.tqi_cw_min = AR5K_TUNE_CWMIN,
		.tqi_cw_max = AR5K_TUNE_CWMAX,
		/* NB: for dynamic turbo, don't enable any other interrupts */
		.tqi_flags = AR5K_TXQ_FLAG_TXDESCINT_ENABLE
	};

	return ath5k_hw_setup_tx_queue(ah, AR5K_TX_QUEUE_BEACON, &qi);
}
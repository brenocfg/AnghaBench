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
struct TYPE_4__ {int dma_beacon_response_time; int sw_beacon_response_time; int cwm_ignore_extcca; int analog_shiftreg; int rx_intr_mitigation; int rimt_last; int rimt_first; int pll_pwrsave; scalar_t__ serialize_regmode; int max_txtrig_level; } ;
struct TYPE_3__ {scalar_t__ macVersion; } ;
struct ath_hw {TYPE_2__ config; int /*<<< orphan*/  is_pciexpress; TYPE_1__ hw_version; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9160 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9285 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_VERSION_5416_PCI ; 
 int MAX_TX_FIFO_THRESHOLD ; 
 int NR_CPUS ; 
 int /*<<< orphan*/  RESET ; 
 scalar_t__ SER_REG_MODE_AUTO ; 
 scalar_t__ SER_REG_MODE_OFF ; 
 scalar_t__ SER_REG_MODE_ON ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int num_possible_cpus () ; 

__attribute__((used)) static void ath9k_hw_init_config(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	ah->config.dma_beacon_response_time = 1;
	ah->config.sw_beacon_response_time = 6;
	ah->config.cwm_ignore_extcca = false;
	ah->config.analog_shiftreg = 1;

	ah->config.rx_intr_mitigation = true;

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		ah->config.rimt_last = 500;
		ah->config.rimt_first = 2000;
	} else {
		ah->config.rimt_last = 250;
		ah->config.rimt_first = 700;
	}

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah))
		ah->config.pll_pwrsave = 7;

	/*
	 * We need this for PCI devices only (Cardbus, PCI, miniPCI)
	 * _and_ if on non-uniprocessor systems (Multiprocessor/HT).
	 * This means we use it for all AR5416 devices, and the few
	 * minor PCI AR9280 devices out there.
	 *
	 * Serialization is required because these devices do not handle
	 * well the case of two concurrent reads/writes due to the latency
	 * involved. During one read/write another read/write can be issued
	 * on another CPU while the previous read/write may still be working
	 * on our hardware, if we hit this case the hardware poops in a loop.
	 * We prevent this by serializing reads and writes.
	 *
	 * This issue is not present on PCI-Express devices or pre-AR5416
	 * devices (legacy, 802.11abg).
	 */
	if (num_possible_cpus() > 1)
		ah->config.serialize_regmode = SER_REG_MODE_AUTO;

	if (NR_CPUS > 1 && ah->config.serialize_regmode == SER_REG_MODE_AUTO) {
		if (ah->hw_version.macVersion == AR_SREV_VERSION_5416_PCI ||
		    ((AR_SREV_9160(ah) || AR_SREV_9280(ah) || AR_SREV_9287(ah)) &&
		     !ah->is_pciexpress)) {
			ah->config.serialize_regmode = SER_REG_MODE_ON;
		} else {
			ah->config.serialize_regmode = SER_REG_MODE_OFF;
		}
	}

	ath_dbg(common, RESET, "serialize_regmode is %d\n",
		ah->config.serialize_regmode);

	if (AR_SREV_9285(ah) || AR_SREV_9271(ah))
		ah->config.max_txtrig_level = MAX_TX_FIFO_THRESHOLD >> 1;
	else
		ah->config.max_txtrig_level = MAX_TX_FIFO_THRESHOLD;
}
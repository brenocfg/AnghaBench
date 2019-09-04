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
struct TYPE_4__ {int /*<<< orphan*/  toggleq; } ;
struct TYPE_3__ {int /*<<< orphan*/  mib_intr; int /*<<< orphan*/  rxeol_intr; int /*<<< orphan*/  rxorn_intr; } ;
struct ath5k_hw {scalar_t__ ah_mac_srev; scalar_t__ tx_pending; scalar_t__ rx_pending; TYPE_2__ rf_kill; TYPE_1__ stats; int /*<<< orphan*/  beacontq; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  imask; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum ath5k_int { ____Placeholder_ath5k_int } ath5k_int ;

/* Variables and functions */
 int AR5K_INT_FATAL ; 
 int AR5K_INT_GPIO ; 
 int AR5K_INT_MIB ; 
 int AR5K_INT_RXEOL ; 
 int AR5K_INT_RXERR ; 
 int AR5K_INT_RXOK ; 
 int AR5K_INT_RXORN ; 
 int AR5K_INT_SWBA ; 
 int AR5K_INT_TXDESC ; 
 int AR5K_INT_TXEOL ; 
 int AR5K_INT_TXERR ; 
 int AR5K_INT_TXOK ; 
 int AR5K_INT_TXURN ; 
 scalar_t__ AR5K_SREV_AR5212 ; 
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_INTR ; 
 int /*<<< orphan*/  ATH5K_DEBUG_RESET ; 
 int /*<<< orphan*/  ATH5K_WARN (struct ath5k_hw*,char*) ; 
 scalar_t__ ATH_AHB ; 
 int /*<<< orphan*/  ATH_STAT_INVALID ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ath5k_ani_mib_intr (struct ath5k_hw*) ; 
 scalar_t__ ath5k_get_bus_type (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_get_isr (struct ath5k_hw*,int*) ; 
 scalar_t__ ath5k_hw_is_intr_pending (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_update_mib_counters (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_update_tx_triglevel (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_intr_calibration_poll (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_schedule_rx (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_schedule_tx (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_set_current_imask (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t
ath5k_intr(int irq, void *dev_id)
{
	struct ath5k_hw *ah = dev_id;
	enum ath5k_int status;
	unsigned int counter = 1000;


	/*
	 * If hw is not ready (or detached) and we get an
	 * interrupt, or if we have no interrupts pending
	 * (that means it's not for us) skip it.
	 *
	 * NOTE: Group 0/1 PCI interface registers are not
	 * supported on WiSOCs, so we can't check for pending
	 * interrupts (ISR belongs to another register group
	 * so we are ok).
	 */
	if (unlikely(test_bit(ATH_STAT_INVALID, ah->status) ||
			((ath5k_get_bus_type(ah) != ATH_AHB) &&
			!ath5k_hw_is_intr_pending(ah))))
		return IRQ_NONE;

	/** Main loop **/
	do {
		ath5k_hw_get_isr(ah, &status);	/* NB: clears IRQ too */

		ATH5K_DBG(ah, ATH5K_DEBUG_INTR, "status 0x%x/0x%x\n",
				status, ah->imask);

		/*
		 * Fatal hw error -> Log and reset
		 *
		 * Fatal errors are unrecoverable so we have to
		 * reset the card. These errors include bus and
		 * dma errors.
		 */
		if (unlikely(status & AR5K_INT_FATAL)) {

			ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
				  "fatal int, resetting\n");
			ieee80211_queue_work(ah->hw, &ah->reset_work);

		/*
		 * RX Overrun -> Count and reset if needed
		 *
		 * Receive buffers are full. Either the bus is busy or
		 * the CPU is not fast enough to process all received
		 * frames.
		 */
		} else if (unlikely(status & AR5K_INT_RXORN)) {

			/*
			 * Older chipsets need a reset to come out of this
			 * condition, but we treat it as RX for newer chips.
			 * We don't know exactly which versions need a reset
			 * this guess is copied from the HAL.
			 */
			ah->stats.rxorn_intr++;

			if (ah->ah_mac_srev < AR5K_SREV_AR5212) {
				ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
					  "rx overrun, resetting\n");
				ieee80211_queue_work(ah->hw, &ah->reset_work);
			} else
				ath5k_schedule_rx(ah);

		} else {

			/* Software Beacon Alert -> Schedule beacon tasklet */
			if (status & AR5K_INT_SWBA)
				tasklet_hi_schedule(&ah->beacontq);

			/*
			 * No more RX descriptors -> Just count
			 *
			 * NB: the hardware should re-read the link when
			 *     RXE bit is written, but it doesn't work at
			 *     least on older hardware revs.
			 */
			if (status & AR5K_INT_RXEOL)
				ah->stats.rxeol_intr++;


			/* TX Underrun -> Bump tx trigger level */
			if (status & AR5K_INT_TXURN)
				ath5k_hw_update_tx_triglevel(ah, true);

			/* RX -> Schedule rx tasklet */
			if (status & (AR5K_INT_RXOK | AR5K_INT_RXERR))
				ath5k_schedule_rx(ah);

			/* TX -> Schedule tx tasklet */
			if (status & (AR5K_INT_TXOK
					| AR5K_INT_TXDESC
					| AR5K_INT_TXERR
					| AR5K_INT_TXEOL))
				ath5k_schedule_tx(ah);

			/* Missed beacon -> TODO
			if (status & AR5K_INT_BMISS)
			*/

			/* MIB event -> Update counters and notify ANI */
			if (status & AR5K_INT_MIB) {
				ah->stats.mib_intr++;
				ath5k_hw_update_mib_counters(ah);
				ath5k_ani_mib_intr(ah);
			}

			/* GPIO -> Notify RFKill layer */
			if (status & AR5K_INT_GPIO)
				tasklet_schedule(&ah->rf_kill.toggleq);

		}

		if (ath5k_get_bus_type(ah) == ATH_AHB)
			break;

	} while (ath5k_hw_is_intr_pending(ah) && --counter > 0);

	/*
	 * Until we handle rx/tx interrupts mask them on IMR
	 *
	 * NOTE: ah->(rx/tx)_pending are set when scheduling the tasklets
	 * and unset after we 've handled the interrupts.
	 */
	if (ah->rx_pending || ah->tx_pending)
		ath5k_set_current_imask(ah);

	if (unlikely(!counter))
		ATH5K_WARN(ah, "too many interrupts, giving up for now\n");

	/* Fire up calibration poll */
	ath5k_intr_calibration_poll(ah);

	return IRQ_HANDLED;
}
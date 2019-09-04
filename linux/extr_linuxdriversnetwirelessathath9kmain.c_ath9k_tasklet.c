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
typedef  int u32 ;
struct ath_softc {int intrstatus; scalar_t__ gtt_cnt; int ps_flags; int /*<<< orphan*/  sc_pcu_lock; struct ath_hw* sc_ah; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  sc_pm_lock; scalar_t__ ps_enabled; int /*<<< orphan*/  intr_lock; } ;
struct TYPE_4__ {int hw_caps; } ;
struct TYPE_3__ {int hw_hang_checks; } ;
struct ath_hw {TYPE_2__ caps; TYPE_1__ config; } ;
struct ath_common {int /*<<< orphan*/  cc_lock; } ;
typedef  enum ath_reset_type { ____Placeholder_ath_reset_type } ath_reset_type ;

/* Variables and functions */
 int ATH9K_HW_CAP_EDMA ; 
 int ATH9K_INT_BB_WATCHDOG ; 
 int ATH9K_INT_FATAL ; 
 int ATH9K_INT_GENTIMER ; 
 int ATH9K_INT_GTT ; 
 int ATH9K_INT_RX ; 
 int ATH9K_INT_RXEOL ; 
 int ATH9K_INT_RXHP ; 
 int ATH9K_INT_RXLP ; 
 int ATH9K_INT_RXORN ; 
 int ATH9K_INT_TSFOOR ; 
 int ATH9K_INT_TX ; 
 int HW_BB_WATCHDOG ; 
 scalar_t__ MAX_GTT_CNT ; 
 int /*<<< orphan*/  PS ; 
 int PS_BEACON_SYNC ; 
 int PS_WAIT_FOR_BEACON ; 
 int /*<<< orphan*/  RESET ; 
 int RESET_TYPE_BB_WATCHDOG ; 
 int RESET_TYPE_FATAL_INT ; 
 int RESET_TYPE_TX_GTT ; 
 scalar_t__ ar9003_hw_bb_watchdog_check (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_bb_watchdog_dbg_info (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_btcoex_handle_interrupt (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath9k_hw_check_alive (struct ath_hw*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_resume_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_queue_reset (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath_gen_timer_isr (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_hw_cycle_counters_update (struct ath_common*) ; 
 int /*<<< orphan*/  ath_rx_tasklet (struct ath_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_tx_edma_tasklet (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_tx_tasklet (struct ath_softc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ath9k_tasklet(unsigned long data)
{
	struct ath_softc *sc = (struct ath_softc *)data;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	enum ath_reset_type type;
	unsigned long flags;
	u32 status;
	u32 rxmask;

	spin_lock_irqsave(&sc->intr_lock, flags);
	status = sc->intrstatus;
	sc->intrstatus = 0;
	spin_unlock_irqrestore(&sc->intr_lock, flags);

	ath9k_ps_wakeup(sc);
	spin_lock(&sc->sc_pcu_lock);

	if (status & ATH9K_INT_FATAL) {
		type = RESET_TYPE_FATAL_INT;
		ath9k_queue_reset(sc, type);
		ath_dbg(common, RESET, "FATAL: Skipping interrupts\n");
		goto out;
	}

	if ((ah->config.hw_hang_checks & HW_BB_WATCHDOG) &&
	    (status & ATH9K_INT_BB_WATCHDOG)) {
		spin_lock_irqsave(&common->cc_lock, flags);
		ath_hw_cycle_counters_update(common);
		ar9003_hw_bb_watchdog_dbg_info(ah);
		spin_unlock_irqrestore(&common->cc_lock, flags);

		if (ar9003_hw_bb_watchdog_check(ah)) {
			type = RESET_TYPE_BB_WATCHDOG;
			ath9k_queue_reset(sc, type);

			ath_dbg(common, RESET,
				"BB_WATCHDOG: Skipping interrupts\n");
			goto out;
		}
	}

	if (status & ATH9K_INT_GTT) {
		sc->gtt_cnt++;

		if ((sc->gtt_cnt >= MAX_GTT_CNT) && !ath9k_hw_check_alive(ah)) {
			type = RESET_TYPE_TX_GTT;
			ath9k_queue_reset(sc, type);
			ath_dbg(common, RESET,
				"GTT: Skipping interrupts\n");
			goto out;
		}
	}

	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	if ((status & ATH9K_INT_TSFOOR) && sc->ps_enabled) {
		/*
		 * TSF sync does not look correct; remain awake to sync with
		 * the next Beacon.
		 */
		ath_dbg(common, PS, "TSFOOR - Sync with next Beacon\n");
		sc->ps_flags |= PS_WAIT_FOR_BEACON | PS_BEACON_SYNC;
	}
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);

	if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		rxmask = (ATH9K_INT_RXHP | ATH9K_INT_RXLP | ATH9K_INT_RXEOL |
			  ATH9K_INT_RXORN);
	else
		rxmask = (ATH9K_INT_RX | ATH9K_INT_RXEOL | ATH9K_INT_RXORN);

	if (status & rxmask) {
		/* Check for high priority Rx first */
		if ((ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) &&
		    (status & ATH9K_INT_RXHP))
			ath_rx_tasklet(sc, 0, true);

		ath_rx_tasklet(sc, 0, false);
	}

	if (status & ATH9K_INT_TX) {
		if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
			/*
			 * For EDMA chips, TX completion is enabled for the
			 * beacon queue, so if a beacon has been transmitted
			 * successfully after a GTT interrupt, the GTT counter
			 * gets reset to zero here.
			 */
			sc->gtt_cnt = 0;

			ath_tx_edma_tasklet(sc);
		} else {
			ath_tx_tasklet(sc);
		}

		wake_up(&sc->tx_wait);
	}

	if (status & ATH9K_INT_GENTIMER)
		ath_gen_timer_isr(sc->sc_ah);

	ath9k_btcoex_handle_interrupt(sc, status);

	/* re-enable hardware interrupt */
	ath9k_hw_resume_interrupts(ah);
out:
	spin_unlock(&sc->sc_pcu_lock);
	ath9k_ps_restore(sc);
}
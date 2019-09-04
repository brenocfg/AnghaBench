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
typedef  int /*<<< orphan*/  u32 ;
struct ath_softc {int intrstatus; int /*<<< orphan*/  intr_tq; int /*<<< orphan*/  sc_pm_lock; int /*<<< orphan*/  ps_flags; struct ath_hw* sc_ah; int /*<<< orphan*/  ps_idle; int /*<<< orphan*/  bcon_tasklet; int /*<<< orphan*/  intr_lock; } ;
struct TYPE_4__ {int hw_caps; } ;
struct TYPE_3__ {int hw_hang_checks; } ;
struct ath_hw {int imask; TYPE_2__ caps; TYPE_1__ config; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum ath9k_int { ____Placeholder_ath9k_int } ath9k_int ;

/* Variables and functions */
 int ATH9K_HW_CAP_AUTOSLEEP ; 
 int ATH9K_INT_BB_WATCHDOG ; 
 int ATH9K_INT_BMISS ; 
 int ATH9K_INT_CST ; 
 int ATH9K_INT_FATAL ; 
 int ATH9K_INT_GENTIMER ; 
 int ATH9K_INT_GTT ; 
 int ATH9K_INT_MCI ; 
 int ATH9K_INT_RX ; 
 int ATH9K_INT_RXEOL ; 
 int ATH9K_INT_RXHP ; 
 int ATH9K_INT_RXLP ; 
 int ATH9K_INT_RXORN ; 
 int ATH9K_INT_SWBA ; 
 int ATH9K_INT_TIM_TIMER ; 
 int ATH9K_INT_TSFOOR ; 
 int ATH9K_INT_TX ; 
 int ATH9K_INT_TXURN ; 
 int /*<<< orphan*/  ATH9K_PM_AWAKE ; 
 scalar_t__ ATH_DBG_WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_OP_HW_RESET ; 
 int /*<<< orphan*/  ATH_OP_INVALID ; 
 int HW_BB_WATCHDOG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PS_WAIT_FOR_BEACON ; 
 int /*<<< orphan*/  ath9k_debug_sync_cause (struct ath_softc*,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_getisr (struct ath_hw*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_hw_intrpend (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_kill_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_setrxabort (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_updatetxtriglevel (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_setpower (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_debug_stat_interrupt (struct ath_softc*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t ath_isr(int irq, void *dev)
{
#define SCHED_INTR (				\
		ATH9K_INT_FATAL |		\
		ATH9K_INT_BB_WATCHDOG |		\
		ATH9K_INT_RXORN |		\
		ATH9K_INT_RXEOL |		\
		ATH9K_INT_RX |			\
		ATH9K_INT_RXLP |		\
		ATH9K_INT_RXHP |		\
		ATH9K_INT_TX |			\
		ATH9K_INT_BMISS |		\
		ATH9K_INT_CST |			\
		ATH9K_INT_GTT |			\
		ATH9K_INT_TSFOOR |		\
		ATH9K_INT_GENTIMER |		\
		ATH9K_INT_MCI)

	struct ath_softc *sc = dev;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	enum ath9k_int status;
	u32 sync_cause = 0;
	bool sched = false;

	/*
	 * The hardware is not ready/present, don't
	 * touch anything. Note this can happen early
	 * on if the IRQ is shared.
	 */
	if (!ah || test_bit(ATH_OP_INVALID, &common->op_flags))
		return IRQ_NONE;

	/* shared irq, not for us */
	if (!ath9k_hw_intrpend(ah))
		return IRQ_NONE;

	/*
	 * Figure out the reason(s) for the interrupt.  Note
	 * that the hal returns a pseudo-ISR that may include
	 * bits we haven't explicitly enabled so we mask the
	 * value to insure we only process bits we requested.
	 */
	ath9k_hw_getisr(ah, &status, &sync_cause); /* NB: clears ISR too */
	ath9k_debug_sync_cause(sc, sync_cause);
	status &= ah->imask;	/* discard unasked-for bits */

	if (test_bit(ATH_OP_HW_RESET, &common->op_flags))
		return IRQ_HANDLED;

	/*
	 * If there are no status bits set, then this interrupt was not
	 * for me (should have been caught above).
	 */
	if (!status)
		return IRQ_NONE;

	/* Cache the status */
	spin_lock(&sc->intr_lock);
	sc->intrstatus |= status;
	spin_unlock(&sc->intr_lock);

	if (status & SCHED_INTR)
		sched = true;

	/*
	 * If a FATAL interrupt is received, we have to reset the chip
	 * immediately.
	 */
	if (status & ATH9K_INT_FATAL)
		goto chip_reset;

	if ((ah->config.hw_hang_checks & HW_BB_WATCHDOG) &&
	    (status & ATH9K_INT_BB_WATCHDOG))
		goto chip_reset;

	if (status & ATH9K_INT_SWBA)
		tasklet_schedule(&sc->bcon_tasklet);

	if (status & ATH9K_INT_TXURN)
		ath9k_hw_updatetxtriglevel(ah, true);

	if (status & ATH9K_INT_RXEOL) {
		ah->imask &= ~(ATH9K_INT_RXEOL | ATH9K_INT_RXORN);
		ath9k_hw_set_interrupts(ah);
	}

	if (!(ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSLEEP))
		if (status & ATH9K_INT_TIM_TIMER) {
			if (ATH_DBG_WARN_ON_ONCE(sc->ps_idle))
				goto chip_reset;
			/* Clear RxAbort bit so that we can
			 * receive frames */
			ath9k_setpower(sc, ATH9K_PM_AWAKE);
			spin_lock(&sc->sc_pm_lock);
			ath9k_hw_setrxabort(sc->sc_ah, 0);
			sc->ps_flags |= PS_WAIT_FOR_BEACON;
			spin_unlock(&sc->sc_pm_lock);
		}

chip_reset:

	ath_debug_stat_interrupt(sc, status);

	if (sched) {
		/* turn off every interrupt */
		ath9k_hw_kill_interrupts(ah);
		tasklet_schedule(&sc->intr_tq);
	}

	return IRQ_HANDLED;

#undef SCHED_INTR
}
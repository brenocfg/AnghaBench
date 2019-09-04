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
typedef  int u32 ;
struct ath_hw {int bb_watchdog_timeout_ms; scalar_t__ curchan; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int AR_PHY_WATCHDOG_CNTL2_MASK ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_CTL_1 ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_CTL_2 ; 
 int AR_PHY_WATCHDOG_IDLE_ENABLE ; 
 int AR_PHY_WATCHDOG_IDLE_MASK ; 
 int AR_PHY_WATCHDOG_IRQ_ENABLE ; 
 int AR_PHY_WATCHDOG_NON_IDLE_ENABLE ; 
 int AR_PHY_WATCHDOG_NON_IDLE_MASK ; 
 int AR_PHY_WATCHDOG_RST_ENABLE ; 
 scalar_t__ IS_CHAN_HT40 (scalar_t__) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RESET ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 

void ar9003_hw_bb_watchdog_config(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 idle_tmo_ms = ah->bb_watchdog_timeout_ms;
	u32 val, idle_count;

	if (!idle_tmo_ms) {
		/* disable IRQ, disable chip-reset for BB panic */
		REG_WRITE(ah, AR_PHY_WATCHDOG_CTL_2,
			  REG_READ(ah, AR_PHY_WATCHDOG_CTL_2) &
			  ~(AR_PHY_WATCHDOG_RST_ENABLE |
			    AR_PHY_WATCHDOG_IRQ_ENABLE));

		/* disable watchdog in non-IDLE mode, disable in IDLE mode */
		REG_WRITE(ah, AR_PHY_WATCHDOG_CTL_1,
			  REG_READ(ah, AR_PHY_WATCHDOG_CTL_1) &
			  ~(AR_PHY_WATCHDOG_NON_IDLE_ENABLE |
			    AR_PHY_WATCHDOG_IDLE_ENABLE));

		ath_dbg(common, RESET, "Disabled BB Watchdog\n");
		return;
	}

	/* enable IRQ, disable chip-reset for BB watchdog */
	val = REG_READ(ah, AR_PHY_WATCHDOG_CTL_2) & AR_PHY_WATCHDOG_CNTL2_MASK;
	REG_WRITE(ah, AR_PHY_WATCHDOG_CTL_2,
		  (val | AR_PHY_WATCHDOG_IRQ_ENABLE) &
		  ~AR_PHY_WATCHDOG_RST_ENABLE);

	/* bound limit to 10 secs */
	if (idle_tmo_ms > 10000)
		idle_tmo_ms = 10000;

	/*
	 * The time unit for watchdog event is 2^15 44/88MHz cycles.
	 *
	 * For HT20 we have a time unit of 2^15/44 MHz = .74 ms per tick
	 * For HT40 we have a time unit of 2^15/88 MHz = .37 ms per tick
	 *
	 * Given we use fast clock now in 5 GHz, these time units should
	 * be common for both 2 GHz and 5 GHz.
	 */
	idle_count = (100 * idle_tmo_ms) / 74;
	if (ah->curchan && IS_CHAN_HT40(ah->curchan))
		idle_count = (100 * idle_tmo_ms) / 37;

	/*
	 * enable watchdog in non-IDLE mode, disable in IDLE mode,
	 * set idle time-out.
	 */
	REG_WRITE(ah, AR_PHY_WATCHDOG_CTL_1,
		  AR_PHY_WATCHDOG_NON_IDLE_ENABLE |
		  AR_PHY_WATCHDOG_IDLE_MASK |
		  (AR_PHY_WATCHDOG_NON_IDLE_MASK & (idle_count << 2)));

	ath_dbg(common, RESET, "Enabled BB Watchdog timeout (%u ms)\n",
		idle_tmo_ms);
}
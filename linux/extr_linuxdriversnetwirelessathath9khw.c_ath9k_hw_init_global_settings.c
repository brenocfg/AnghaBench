#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int ackto; scalar_t__ enabled; } ;
struct ath_hw {scalar_t__ misc_mode; int slottime; int coverage_class; scalar_t__ globaltxtimeout; TYPE_1__ dynack; struct ath9k_channel* curchan; } ;
struct ath_common {int clockrate; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_D_GBL_IFS_EIFS ; 
 int AR_D_GBL_IFS_EIFS_ASYNC_FIFO ; 
 int /*<<< orphan*/  AR_PCU_MISC ; 
 scalar_t__ AR_SREV_9287 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287_13_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_TXSIFS ; 
 int AR_TXSIFS_ACK_SHIFT ; 
 int AR_TXSIFS_TIME ; 
 int /*<<< orphan*/  AR_USEC ; 
 scalar_t__ AR_USEC_ASYNC_FIFO ; 
 int AR_USEC_RX_LAT ; 
 int AR_USEC_TX_LAT ; 
 int AR_USEC_USEC ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel const*) ; 
 scalar_t__ IS_CHAN_5GHZ (struct ath9k_channel const*) ; 
 scalar_t__ IS_CHAN_A_FAST_CLOCK (struct ath_hw*,struct ath9k_channel const*) ; 
 scalar_t__ IS_CHAN_HALF_RATE (struct ath9k_channel const*) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (struct ath9k_channel const*) ; 
 int MS (scalar_t__,int) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESET ; 
 int SM (int,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_mac_to_clks (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_set_ack_timeout (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_set_cts_timeout (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_set_global_txtimeout (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ath9k_hw_set_sifs_time (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_setslottime (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,scalar_t__) ; 

void ath9k_hw_init_global_settings(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	const struct ath9k_channel *chan = ah->curchan;
	int acktimeout, ctstimeout, ack_offset = 0;
	int slottime;
	int sifstime;
	int rx_lat = 0, tx_lat = 0, eifs = 0, ack_shift = 0;
	u32 reg;

	ath_dbg(ath9k_hw_common(ah), RESET, "ah->misc_mode 0x%x\n",
		ah->misc_mode);

	if (!chan)
		return;

	if (ah->misc_mode != 0)
		REG_SET_BIT(ah, AR_PCU_MISC, ah->misc_mode);

	if (IS_CHAN_A_FAST_CLOCK(ah, chan))
		rx_lat = 41;
	else
		rx_lat = 37;
	tx_lat = 54;

	if (IS_CHAN_5GHZ(chan))
		sifstime = 16;
	else
		sifstime = 10;

	if (IS_CHAN_HALF_RATE(chan)) {
		eifs = 175;
		rx_lat *= 2;
		tx_lat *= 2;
		if (IS_CHAN_A_FAST_CLOCK(ah, chan))
		    tx_lat += 11;

		sifstime = 32;
		ack_offset = 16;
		ack_shift = 3;
		slottime = 13;
	} else if (IS_CHAN_QUARTER_RATE(chan)) {
		eifs = 340;
		rx_lat = (rx_lat * 4) - 1;
		tx_lat *= 4;
		if (IS_CHAN_A_FAST_CLOCK(ah, chan))
		    tx_lat += 22;

		sifstime = 64;
		ack_offset = 32;
		ack_shift = 1;
		slottime = 21;
	} else {
		if (AR_SREV_9287(ah) && AR_SREV_9287_13_OR_LATER(ah)) {
			eifs = AR_D_GBL_IFS_EIFS_ASYNC_FIFO;
			reg = AR_USEC_ASYNC_FIFO;
		} else {
			eifs = REG_READ(ah, AR_D_GBL_IFS_EIFS)/
				common->clockrate;
			reg = REG_READ(ah, AR_USEC);
		}
		rx_lat = MS(reg, AR_USEC_RX_LAT);
		tx_lat = MS(reg, AR_USEC_TX_LAT);

		slottime = ah->slottime;
	}

	/* As defined by IEEE 802.11-2007 17.3.8.6 */
	slottime += 3 * ah->coverage_class;
	acktimeout = slottime + sifstime + ack_offset;
	ctstimeout = acktimeout;

	/*
	 * Workaround for early ACK timeouts, add an offset to match the
	 * initval's 64us ack timeout value. Use 48us for the CTS timeout.
	 * This was initially only meant to work around an issue with delayed
	 * BA frames in some implementations, but it has been found to fix ACK
	 * timeout issues in other cases as well.
	 */
	if (IS_CHAN_2GHZ(chan) &&
	    !IS_CHAN_HALF_RATE(chan) && !IS_CHAN_QUARTER_RATE(chan)) {
		acktimeout += 64 - sifstime - ah->slottime;
		ctstimeout += 48 - sifstime - ah->slottime;
	}

	if (ah->dynack.enabled) {
		acktimeout = ah->dynack.ackto;
		ctstimeout = acktimeout;
		slottime = (acktimeout - 3) / 2;
	} else {
		ah->dynack.ackto = acktimeout;
	}

	ath9k_hw_set_sifs_time(ah, sifstime);
	ath9k_hw_setslottime(ah, slottime);
	ath9k_hw_set_ack_timeout(ah, acktimeout);
	ath9k_hw_set_cts_timeout(ah, ctstimeout);
	if (ah->globaltxtimeout != (u32) -1)
		ath9k_hw_set_global_txtimeout(ah, ah->globaltxtimeout);

	REG_WRITE(ah, AR_D_GBL_IFS_EIFS, ath9k_hw_mac_to_clks(ah, eifs));
	REG_RMW(ah, AR_USEC,
		(common->clockrate - 1) |
		SM(rx_lat, AR_USEC_RX_LAT) |
		SM(tx_lat, AR_USEC_TX_LAT),
		AR_USEC_TX_LAT | AR_USEC_RX_LAT | AR_USEC_USEC);

	if (IS_CHAN_HALF_RATE(chan) || IS_CHAN_QUARTER_RATE(chan))
		REG_RMW(ah, AR_TXSIFS,
			sifstime | SM(ack_shift, AR_TXSIFS_ACK_SHIFT),
			(AR_TXSIFS_TIME | AR_TXSIFS_ACK_SHIFT));
}
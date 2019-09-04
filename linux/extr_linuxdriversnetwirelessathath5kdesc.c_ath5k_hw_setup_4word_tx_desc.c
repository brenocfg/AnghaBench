#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct ath5k_hw_4w_tx_ctl {unsigned int tx_control_0; unsigned int tx_control_1; unsigned int tx_control_2; unsigned int tx_control_3; } ;
struct TYPE_4__ {scalar_t__ txp_offset; } ;
struct ath5k_hw {TYPE_1__ ah_txpower; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_stat; struct ath5k_hw_4w_tx_ctl tx_ctl; } ;
struct TYPE_6__ {TYPE_2__ ds_tx5212; } ;
struct ath5k_desc {TYPE_3__ ud; } ;
typedef  enum ath5k_pkt_type { ____Placeholder_ath5k_pkt_type } ath5k_pkt_type ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL0_ANT_MODE_XMIT ; 
 unsigned int AR5K_4W_TX_DESC_CTL0_CLRDMASK ; 
 unsigned int AR5K_4W_TX_DESC_CTL0_CTSENA ; 
 unsigned int AR5K_4W_TX_DESC_CTL0_ENCRYPT_KEY_VALID ; 
 unsigned int AR5K_4W_TX_DESC_CTL0_FRAME_LEN ; 
 unsigned int AR5K_4W_TX_DESC_CTL0_INTREQ ; 
 unsigned int AR5K_4W_TX_DESC_CTL0_RTSENA ; 
 unsigned int AR5K_4W_TX_DESC_CTL0_VEOL ; 
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL0_XMIT_POWER ; 
 unsigned int AR5K_4W_TX_DESC_CTL1_BUF_LEN ; 
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL1_ENCRYPT_KEY_IDX ; 
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL1_FRAME_TYPE ; 
 unsigned int AR5K_4W_TX_DESC_CTL1_NOACK ; 
 unsigned int AR5K_4W_TX_DESC_CTL2_RTS_DURATION ; 
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL2_XMIT_TRIES0 ; 
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL3_RTS_CTS_RATE ; 
 unsigned int AR5K_4W_TX_DESC_CTL3_XMIT_RATE0 ; 
 int AR5K_PKT_TYPE_BEACON ; 
 unsigned int AR5K_REG_SM (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int AR5K_TUNE_MAX_TXPOWER ; 
 unsigned int AR5K_TXDESC_CLRDMASK ; 
 unsigned int AR5K_TXDESC_CTSENA ; 
 unsigned int AR5K_TXDESC_INTREQ ; 
 unsigned int AR5K_TXDESC_NOACK ; 
 unsigned int AR5K_TXDESC_RTSENA ; 
 unsigned int AR5K_TXDESC_VEOL ; 
 unsigned int AR5K_TXKEYIX_INVALID ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*) ; 
 int EINVAL ; 
 unsigned int FCS_LEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int roundup (unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ath5k_hw_setup_4word_tx_desc(struct ath5k_hw *ah,
			struct ath5k_desc *desc,
			unsigned int pkt_len, unsigned int hdr_len,
			int padsize,
			enum ath5k_pkt_type type,
			unsigned int tx_power,
			unsigned int tx_rate0, unsigned int tx_tries0,
			unsigned int key_index,
			unsigned int antenna_mode,
			unsigned int flags,
			unsigned int rtscts_rate, unsigned int rtscts_duration)
{
	struct ath5k_hw_4w_tx_ctl *tx_ctl;
	unsigned int frame_len;

	/*
	 * Use local variables for these to reduce load/store access on
	 * uncached memory
	 */
	u32 txctl0 = 0, txctl1 = 0, txctl2 = 0, txctl3 = 0;

	tx_ctl = &desc->ud.ds_tx5212.tx_ctl;

	/*
	 * Validate input
	 * - Zero retries don't make sense.
	 * - A zero rate will put the HW into a mode where it continuously sends
	 *   noise on the channel, so it is important to avoid this.
	 */
	if (unlikely(tx_tries0 == 0)) {
		ATH5K_ERR(ah, "zero retries\n");
		WARN_ON(1);
		return -EINVAL;
	}
	if (unlikely(tx_rate0 == 0)) {
		ATH5K_ERR(ah, "zero rate\n");
		WARN_ON(1);
		return -EINVAL;
	}

	tx_power += ah->ah_txpower.txp_offset;
	if (tx_power > AR5K_TUNE_MAX_TXPOWER)
		tx_power = AR5K_TUNE_MAX_TXPOWER;

	/* Clear descriptor status area */
	memset(&desc->ud.ds_tx5212.tx_stat, 0,
	       sizeof(desc->ud.ds_tx5212.tx_stat));

	/* Setup control descriptor */

	/* Verify and set frame length */

	/* remove padding we might have added before */
	frame_len = pkt_len - padsize + FCS_LEN;

	if (frame_len & ~AR5K_4W_TX_DESC_CTL0_FRAME_LEN)
		return -EINVAL;

	txctl0 = frame_len & AR5K_4W_TX_DESC_CTL0_FRAME_LEN;

	/* Verify and set buffer length */

	/* NB: beacon's BufLen must be a multiple of 4 bytes */
	if (type == AR5K_PKT_TYPE_BEACON)
		pkt_len = roundup(pkt_len, 4);

	if (pkt_len & ~AR5K_4W_TX_DESC_CTL1_BUF_LEN)
		return -EINVAL;

	txctl1 = pkt_len & AR5K_4W_TX_DESC_CTL1_BUF_LEN;

	txctl0 |= AR5K_REG_SM(tx_power, AR5K_4W_TX_DESC_CTL0_XMIT_POWER) |
		  AR5K_REG_SM(antenna_mode, AR5K_4W_TX_DESC_CTL0_ANT_MODE_XMIT);
	txctl1 |= AR5K_REG_SM(type, AR5K_4W_TX_DESC_CTL1_FRAME_TYPE);
	txctl2 = AR5K_REG_SM(tx_tries0, AR5K_4W_TX_DESC_CTL2_XMIT_TRIES0);
	txctl3 = tx_rate0 & AR5K_4W_TX_DESC_CTL3_XMIT_RATE0;

#define _TX_FLAGS(_c, _flag)					\
	if (flags & AR5K_TXDESC_##_flag) {			\
		txctl##_c |= AR5K_4W_TX_DESC_CTL##_c##_##_flag;	\
	}

	_TX_FLAGS(0, CLRDMASK);
	_TX_FLAGS(0, VEOL);
	_TX_FLAGS(0, INTREQ);
	_TX_FLAGS(0, RTSENA);
	_TX_FLAGS(0, CTSENA);
	_TX_FLAGS(1, NOACK);

#undef _TX_FLAGS

	/*
	 * WEP crap
	 */
	if (key_index != AR5K_TXKEYIX_INVALID) {
		txctl0 |= AR5K_4W_TX_DESC_CTL0_ENCRYPT_KEY_VALID;
		txctl1 |= AR5K_REG_SM(key_index,
				AR5K_4W_TX_DESC_CTL1_ENCRYPT_KEY_IDX);
	}

	/*
	 * RTS/CTS
	 */
	if (flags & (AR5K_TXDESC_RTSENA | AR5K_TXDESC_CTSENA)) {
		if ((flags & AR5K_TXDESC_RTSENA) &&
				(flags & AR5K_TXDESC_CTSENA))
			return -EINVAL;
		txctl2 |= rtscts_duration & AR5K_4W_TX_DESC_CTL2_RTS_DURATION;
		txctl3 |= AR5K_REG_SM(rtscts_rate,
				AR5K_4W_TX_DESC_CTL3_RTS_CTS_RATE);
	}

	tx_ctl->tx_control_0 = txctl0;
	tx_ctl->tx_control_1 = txctl1;
	tx_ctl->tx_control_2 = txctl2;
	tx_ctl->tx_control_3 = txctl3;

	return 0;
}
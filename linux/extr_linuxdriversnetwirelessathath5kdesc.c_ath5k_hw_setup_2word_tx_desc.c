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
typedef  unsigned int u32 ;
struct ath5k_hw_5210_tx_desc {int dummy; } ;
struct ath5k_hw_2w_tx_ctl {unsigned int tx_control_0; unsigned int tx_control_1; } ;
struct ath5k_hw {scalar_t__ ah_version; } ;
struct TYPE_4__ {struct ath5k_hw_2w_tx_ctl tx_ctl; } ;
struct TYPE_3__ {TYPE_2__ ds_tx5210; } ;
struct ath5k_desc {TYPE_1__ ud; } ;
typedef  enum ath5k_pkt_type { ____Placeholder_ath5k_pkt_type } ath5k_pkt_type ;

/* Variables and functions */
 unsigned int AR5K_2W_TX_DESC_CTL0_ANT_MODE_XMIT ; 
 int AR5K_2W_TX_DESC_CTL0_CLRDMASK ; 
 int AR5K_2W_TX_DESC_CTL0_ENCRYPT_KEY_VALID ; 
 unsigned int AR5K_2W_TX_DESC_CTL0_FRAME_LEN ; 
 unsigned int AR5K_2W_TX_DESC_CTL0_FRAME_TYPE_5210 ; 
 unsigned int AR5K_2W_TX_DESC_CTL0_HEADER_LEN_5210 ; 
 int AR5K_2W_TX_DESC_CTL0_INTREQ ; 
 int AR5K_2W_TX_DESC_CTL0_RTSENA ; 
 int AR5K_2W_TX_DESC_CTL0_VEOL_5211 ; 
 unsigned int AR5K_2W_TX_DESC_CTL0_XMIT_RATE ; 
 unsigned int AR5K_2W_TX_DESC_CTL1_BUF_LEN ; 
 unsigned int AR5K_2W_TX_DESC_CTL1_ENC_KEY_IDX ; 
 unsigned int AR5K_2W_TX_DESC_CTL1_FRAME_TYPE_5211 ; 
 int AR5K_2W_TX_DESC_CTL1_NOACK_5211 ; 
 unsigned int AR5K_2W_TX_DESC_CTL1_RTS_DURATION_5210 ; 
 scalar_t__ AR5K_AR5210 ; 
 unsigned int AR5K_AR5210_TX_DESC_FRAME_TYPE_NO_DELAY ; 
 unsigned int AR5K_AR5210_TX_DESC_FRAME_TYPE_PIFS ; 
 scalar_t__ AR5K_AR5211 ; 
#define  AR5K_PKT_TYPE_BEACON 130 
#define  AR5K_PKT_TYPE_PIFS 129 
#define  AR5K_PKT_TYPE_PROBE_RESP 128 
 int AR5K_REG_SM (unsigned int,unsigned int) ; 
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
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 unsigned int roundup (unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ath5k_hw_setup_2word_tx_desc(struct ath5k_hw *ah,
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
	u32 frame_type;
	struct ath5k_hw_2w_tx_ctl *tx_ctl;
	unsigned int frame_len;

	tx_ctl = &desc->ud.ds_tx5210.tx_ctl;

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

	/* Clear descriptor */
	memset(&desc->ud.ds_tx5210, 0, sizeof(struct ath5k_hw_5210_tx_desc));

	/* Setup control descriptor */

	/* Verify and set frame length */

	/* remove padding we might have added before */
	frame_len = pkt_len - padsize + FCS_LEN;

	if (frame_len & ~AR5K_2W_TX_DESC_CTL0_FRAME_LEN)
		return -EINVAL;

	tx_ctl->tx_control_0 = frame_len & AR5K_2W_TX_DESC_CTL0_FRAME_LEN;

	/* Verify and set buffer length */

	/* NB: beacon's BufLen must be a multiple of 4 bytes */
	if (type == AR5K_PKT_TYPE_BEACON)
		pkt_len = roundup(pkt_len, 4);

	if (pkt_len & ~AR5K_2W_TX_DESC_CTL1_BUF_LEN)
		return -EINVAL;

	tx_ctl->tx_control_1 = pkt_len & AR5K_2W_TX_DESC_CTL1_BUF_LEN;

	/*
	 * Verify and set header length (only 5210)
	 */
	if (ah->ah_version == AR5K_AR5210) {
		if (hdr_len & ~AR5K_2W_TX_DESC_CTL0_HEADER_LEN_5210)
			return -EINVAL;
		tx_ctl->tx_control_0 |=
			AR5K_REG_SM(hdr_len, AR5K_2W_TX_DESC_CTL0_HEADER_LEN_5210);
	}

	/*Differences between 5210-5211*/
	if (ah->ah_version == AR5K_AR5210) {
		switch (type) {
		case AR5K_PKT_TYPE_BEACON:
		case AR5K_PKT_TYPE_PROBE_RESP:
			frame_type = AR5K_AR5210_TX_DESC_FRAME_TYPE_NO_DELAY;
			break;
		case AR5K_PKT_TYPE_PIFS:
			frame_type = AR5K_AR5210_TX_DESC_FRAME_TYPE_PIFS;
			break;
		default:
			frame_type = type;
			break;
		}

		tx_ctl->tx_control_0 |=
		AR5K_REG_SM(frame_type, AR5K_2W_TX_DESC_CTL0_FRAME_TYPE_5210) |
		AR5K_REG_SM(tx_rate0, AR5K_2W_TX_DESC_CTL0_XMIT_RATE);

	} else {
		tx_ctl->tx_control_0 |=
			AR5K_REG_SM(tx_rate0, AR5K_2W_TX_DESC_CTL0_XMIT_RATE) |
			AR5K_REG_SM(antenna_mode,
				AR5K_2W_TX_DESC_CTL0_ANT_MODE_XMIT);
		tx_ctl->tx_control_1 |=
			AR5K_REG_SM(type, AR5K_2W_TX_DESC_CTL1_FRAME_TYPE_5211);
	}

#define _TX_FLAGS(_c, _flag)					\
	if (flags & AR5K_TXDESC_##_flag) {			\
		tx_ctl->tx_control_##_c |=			\
			AR5K_2W_TX_DESC_CTL##_c##_##_flag;	\
	}
#define _TX_FLAGS_5211(_c, _flag)					\
	if (flags & AR5K_TXDESC_##_flag) {				\
		tx_ctl->tx_control_##_c |=				\
			AR5K_2W_TX_DESC_CTL##_c##_##_flag##_5211;	\
	}
	_TX_FLAGS(0, CLRDMASK);
	_TX_FLAGS(0, INTREQ);
	_TX_FLAGS(0, RTSENA);

	if (ah->ah_version == AR5K_AR5211) {
		_TX_FLAGS_5211(0, VEOL);
		_TX_FLAGS_5211(1, NOACK);
	}

#undef _TX_FLAGS
#undef _TX_FLAGS_5211

	/*
	 * WEP crap
	 */
	if (key_index != AR5K_TXKEYIX_INVALID) {
		tx_ctl->tx_control_0 |=
			AR5K_2W_TX_DESC_CTL0_ENCRYPT_KEY_VALID;
		tx_ctl->tx_control_1 |=
			AR5K_REG_SM(key_index,
			AR5K_2W_TX_DESC_CTL1_ENC_KEY_IDX);
	}

	/*
	 * RTS/CTS Duration [5210 ?]
	 */
	if ((ah->ah_version == AR5K_AR5210) &&
			(flags & (AR5K_TXDESC_RTSENA | AR5K_TXDESC_CTSENA)))
		tx_ctl->tx_control_1 |= rtscts_duration &
				AR5K_2W_TX_DESC_CTL1_RTS_DURATION_5210;

	return 0;
}
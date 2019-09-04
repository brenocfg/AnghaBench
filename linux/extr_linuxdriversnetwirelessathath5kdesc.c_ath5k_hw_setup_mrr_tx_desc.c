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
typedef  scalar_t__ u_int ;
struct ath5k_hw_4w_tx_ctl {int /*<<< orphan*/  tx_control_3; int /*<<< orphan*/  tx_control_2; } ;
struct ath5k_hw {scalar_t__ ah_version; } ;
struct TYPE_3__ {struct ath5k_hw_4w_tx_ctl tx_ctl; } ;
struct TYPE_4__ {TYPE_1__ ds_tx5212; } ;
struct ath5k_desc {TYPE_2__ ud; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL2_XMIT_TRIES1 ; 
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL2_XMIT_TRIES2 ; 
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL2_XMIT_TRIES3 ; 
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL3_XMIT_RATE1 ; 
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL3_XMIT_RATE2 ; 
 int /*<<< orphan*/  AR5K_4W_TX_DESC_CTL3_XMIT_RATE3 ; 
 scalar_t__ AR5K_AR5212 ; 
 int /*<<< orphan*/  AR5K_REG_SM (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ unlikely (int) ; 

int
ath5k_hw_setup_mrr_tx_desc(struct ath5k_hw *ah,
			struct ath5k_desc *desc,
			u_int tx_rate1, u_int tx_tries1,
			u_int tx_rate2, u_int tx_tries2,
			u_int tx_rate3, u_int tx_tries3)
{
	struct ath5k_hw_4w_tx_ctl *tx_ctl;

	/* no mrr support for cards older than 5212 */
	if (ah->ah_version < AR5K_AR5212)
		return 0;

	/*
	 * Rates can be 0 as long as the retry count is 0 too.
	 * A zero rate and nonzero retry count will put the HW into a mode where
	 * it continuously sends noise on the channel, so it is important to
	 * avoid this.
	 */
	if (unlikely((tx_rate1 == 0 && tx_tries1 != 0) ||
		     (tx_rate2 == 0 && tx_tries2 != 0) ||
		     (tx_rate3 == 0 && tx_tries3 != 0))) {
		ATH5K_ERR(ah, "zero rate\n");
		WARN_ON(1);
		return -EINVAL;
	}

	if (ah->ah_version == AR5K_AR5212) {
		tx_ctl = &desc->ud.ds_tx5212.tx_ctl;

#define _XTX_TRIES(_n)							\
	if (tx_tries##_n) {						\
		tx_ctl->tx_control_2 |=					\
		    AR5K_REG_SM(tx_tries##_n,				\
		    AR5K_4W_TX_DESC_CTL2_XMIT_TRIES##_n);		\
		tx_ctl->tx_control_3 |=					\
		    AR5K_REG_SM(tx_rate##_n,				\
		    AR5K_4W_TX_DESC_CTL3_XMIT_RATE##_n);		\
	}

		_XTX_TRIES(1);
		_XTX_TRIES(2);
		_XTX_TRIES(3);

#undef _XTX_TRIES

		return 1;
	}

	return 0;
}
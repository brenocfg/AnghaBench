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
struct TYPE_4__ {int rx_chainmask; } ;
struct ath_hw {TYPE_1__* caldata; TYPE_2__ caps; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** rtt_table; } ;

/* Variables and functions */
 int AR9300_MAX_CHAINS ; 
 int /*<<< orphan*/  CALIBRATE ; 
 int MAX_RTT_TABLE_ENTRY ; 
 int /*<<< orphan*/  ar9003_hw_rtt_load_hist_entry (struct ath_hw*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 

void ar9003_hw_rtt_load_hist(struct ath_hw *ah)
{
	int chain, i;

	for (chain = 0; chain < AR9300_MAX_CHAINS; chain++) {
		if (!(ah->caps.rx_chainmask & (1 << chain)))
			continue;
		for (i = 0; i < MAX_RTT_TABLE_ENTRY; i++) {
			ar9003_hw_rtt_load_hist_entry(ah, chain, i,
					      ah->caldata->rtt_table[chain][i]);
			ath_dbg(ath9k_hw_common(ah), CALIBRATE,
				"Load RTT value at idx %d, chain %d: 0x%x\n",
				i, chain, ah->caldata->rtt_table[chain][i]);
		}
	}
}
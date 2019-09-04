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
struct TYPE_3__ {int rx_chainmask; } ;
struct ath_hw {TYPE_2__* caldata; TYPE_1__ caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  cal_flags; } ;

/* Variables and functions */
 int AR9300_MAX_CHAINS ; 
 int MAX_RTT_TABLE_ENTRY ; 
 int /*<<< orphan*/  RTT_DONE ; 
 int /*<<< orphan*/  ar9003_hw_rtt_load_hist_entry (struct ath_hw*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ar9003_hw_rtt_clear_hist(struct ath_hw *ah)
{
	int chain, i;

	for (chain = 0; chain < AR9300_MAX_CHAINS; chain++) {
		if (!(ah->caps.rx_chainmask & (1 << chain)))
			continue;
		for (i = 0; i < MAX_RTT_TABLE_ENTRY; i++)
			ar9003_hw_rtt_load_hist_entry(ah, chain, i, 0);
	}

	if (ah->caldata)
		clear_bit(RTT_DONE, &ah->caldata->cal_flags);
}
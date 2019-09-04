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
struct TYPE_2__ {int /*<<< orphan*/ * nfval; scalar_t__ index; } ;
struct ath5k_hw {TYPE_1__ ah_nfcal_hist; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_TUNE_CCA_MAX_GOOD_VALUE ; 
 int ATH5K_NF_CAL_HIST_MAX ; 

void
ath5k_hw_init_nfcal_hist(struct ath5k_hw *ah)
{
	int i;

	ah->ah_nfcal_hist.index = 0;
	for (i = 0; i < ATH5K_NF_CAL_HIST_MAX; i++)
		ah->ah_nfcal_hist.nfval[i] = AR5K_TUNE_CCA_MAX_GOOD_VALUE;
}
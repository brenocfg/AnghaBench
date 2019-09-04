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
struct TYPE_2__ {int /*<<< orphan*/  nfval; } ;
struct ath5k_hw {TYPE_1__ ah_nfcal_hist; } ;
typedef  int /*<<< orphan*/  sort ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_CALIBRATE ; 
 int ATH5K_NF_CAL_HIST_MAX ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s16
ath5k_hw_get_median_noise_floor(struct ath5k_hw *ah)
{
	s16 sort[ATH5K_NF_CAL_HIST_MAX];
	s16 tmp;
	int i, j;

	memcpy(sort, ah->ah_nfcal_hist.nfval, sizeof(sort));
	for (i = 0; i < ATH5K_NF_CAL_HIST_MAX - 1; i++) {
		for (j = 1; j < ATH5K_NF_CAL_HIST_MAX - i; j++) {
			if (sort[j] > sort[j - 1]) {
				tmp = sort[j];
				sort[j] = sort[j - 1];
				sort[j - 1] = tmp;
			}
		}
	}
	for (i = 0; i < ATH5K_NF_CAL_HIST_MAX; i++) {
		ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
			"cal %d:%d\n", i, sort[i]);
	}
	return sort[(ATH5K_NF_CAL_HIST_MAX - 1) / 2];
}
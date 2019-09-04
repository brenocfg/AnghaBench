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
struct ath_hw {scalar_t__* tx_power; } ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int AR5008_HT20_SHIFT ; 
 int AR5008_HT40_SHIFT ; 
 int AR5008_HT_SS_RATES ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void ar5008_hw_init_txpower_ht(struct ath_hw *ah, int16_t *rate_array,
				      int ss_offset, int ds_offset,
				      bool is_40, int ht40_delta)
{
	int i, mcs_idx = (is_40) ? AR5008_HT40_SHIFT : AR5008_HT20_SHIFT;

	for (i = ss_offset; i < ss_offset + AR5008_HT_SS_RATES; i++) {
		ah->tx_power[i] = rate_array[mcs_idx] + ht40_delta;
		mcs_idx++;
	}
	memcpy(&ah->tx_power[ds_offset], &ah->tx_power[ss_offset],
	       AR5008_HT_SS_RATES);
}
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
struct ath_hw {int /*<<< orphan*/ * tx_power; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int AR5008_OFDM_RATES ; 

__attribute__((used)) static void ar5008_hw_init_txpower_ofdm(struct ath_hw *ah, int16_t *rate_array,
					int offset)
{
	int i, idx = 0;

	for (i = offset; i < offset + AR5008_OFDM_RATES; i++) {
		ah->tx_power[i] = rate_array[idx];
		idx++;
	}
}
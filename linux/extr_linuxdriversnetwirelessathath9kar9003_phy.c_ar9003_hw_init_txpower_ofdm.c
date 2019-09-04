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
typedef  int /*<<< orphan*/  u8 ;
struct ath_hw {int /*<<< orphan*/ * tx_power; } ;

/* Variables and functions */
 int AR9300_OFDM_RATES ; 
 int* ofdm2pwr ; 

__attribute__((used)) static void ar9003_hw_init_txpower_ofdm(struct ath_hw *ah, u8 *rate_array,
					int offset)
{
	int i, j;

	for (i = offset; i < offset + AR9300_OFDM_RATES; i++) {
		/* OFDM rate to power table idx */
		j = ofdm2pwr[i - offset];
		ah->tx_power[i] = rate_array[j];
	}
}
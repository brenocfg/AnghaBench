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
typedef  int u32 ;
typedef  int u16 ;
struct ieee80211_channel {int center_freq; } ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_RF_BUFFER ; 
 int /*<<< orphan*/  AR5K_RF_BUFFER_CONTROL_5 ; 
 int EINVAL ; 
 int ath5k_hw_bitswap (int,int) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath5k_hw_rf5112_channel(struct ath5k_hw *ah,
		struct ieee80211_channel *channel)
{
	u32 data, data0, data1, data2;
	u16 c;

	data = data0 = data1 = data2 = 0;
	c = channel->center_freq;

	/* My guess based on code:
	 * 2GHz RF has 2 synth modes, one with a Local Oscillator
	 * at 2224Hz and one with a LO at 2192Hz. IF is 1520Hz
	 * (3040/2). data0 is used to set the PLL divider and data1
	 * selects synth mode. */
	if (c < 4800) {
		/* Channel 14 and all frequencies with 2Hz spacing
		 * below/above (non-standard channels) */
		if (!((c - 2224) % 5)) {
			/* Same as (c - 2224) / 5 */
			data0 = ((2 * (c - 704)) - 3040) / 10;
			data1 = 1;
		/* Channel 1 and all frequencies with 5Hz spacing
		 * below/above (standard channels without channel 14) */
		} else if (!((c - 2192) % 5)) {
			/* Same as (c - 2192) / 5 */
			data0 = ((2 * (c - 672)) - 3040) / 10;
			data1 = 0;
		} else
			return -EINVAL;

		data0 = ath5k_hw_bitswap((data0 << 2) & 0xff, 8);
	/* This is more complex, we have a single synthesizer with
	 * 4 reference clock settings (?) based on frequency spacing
	 * and set using data2. LO is at 4800Hz and data0 is again used
	 * to set some divider.
	 *
	 * NOTE: There is an old atheros presentation at Stanford
	 * that mentions a method called dual direct conversion
	 * with 1GHz sliding IF for RF5110. Maybe that's what we
	 * have here, or an updated version. */
	} else if ((c % 5) != 2 || c > 5435) {
		if (!(c % 20) && c >= 5120) {
			data0 = ath5k_hw_bitswap(((c - 4800) / 20 << 2), 8);
			data2 = ath5k_hw_bitswap(3, 2);
		} else if (!(c % 10)) {
			data0 = ath5k_hw_bitswap(((c - 4800) / 10 << 1), 8);
			data2 = ath5k_hw_bitswap(2, 2);
		} else if (!(c % 5)) {
			data0 = ath5k_hw_bitswap((c - 4800) / 5, 8);
			data2 = ath5k_hw_bitswap(1, 2);
		} else
			return -EINVAL;
	} else {
		data0 = ath5k_hw_bitswap((10 * (c - 2 - 4800)) / 25 + 1, 8);
		data2 = ath5k_hw_bitswap(0, 2);
	}

	data = (data0 << 4) | (data1 << 1) | (data2 << 2) | 0x1001;

	ath5k_hw_reg_write(ah, data & 0xff, AR5K_RF_BUFFER);
	ath5k_hw_reg_write(ah, (data >> 8) & 0x7f, AR5K_RF_BUFFER_CONTROL_5);

	return 0;
}
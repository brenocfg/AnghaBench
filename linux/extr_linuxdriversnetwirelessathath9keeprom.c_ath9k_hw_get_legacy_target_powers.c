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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct chan_centers {scalar_t__ ext_center; scalar_t__ ctl_center; } ;
struct cal_target_power_leg {scalar_t__ bChannel; scalar_t__* tPow2x; } ;
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR5416_BCHAN_UNUSED ; 
 int /*<<< orphan*/  IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ ath9k_hw_fbin2freq (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_get_channel_centers (struct ath_hw*,struct ath9k_channel*,struct chan_centers*) ; 
 scalar_t__ ath9k_hw_interpolate (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void ath9k_hw_get_legacy_target_powers(struct ath_hw *ah,
				       struct ath9k_channel *chan,
				       struct cal_target_power_leg *powInfo,
				       u16 numChannels,
				       struct cal_target_power_leg *pNewPower,
				       u16 numRates, bool isExtTarget)
{
	struct chan_centers centers;
	u16 clo, chi;
	int i;
	int matchIndex = -1, lowIndex = -1;
	u16 freq;

	ath9k_hw_get_channel_centers(ah, chan, &centers);
	freq = (isExtTarget) ? centers.ext_center : centers.ctl_center;

	if (freq <= ath9k_hw_fbin2freq(powInfo[0].bChannel,
				       IS_CHAN_2GHZ(chan))) {
		matchIndex = 0;
	} else {
		for (i = 0; (i < numChannels) &&
			     (powInfo[i].bChannel != AR5416_BCHAN_UNUSED); i++) {
			if (freq == ath9k_hw_fbin2freq(powInfo[i].bChannel,
						       IS_CHAN_2GHZ(chan))) {
				matchIndex = i;
				break;
			} else if (freq < ath9k_hw_fbin2freq(powInfo[i].bChannel,
						IS_CHAN_2GHZ(chan)) && i > 0 &&
				   freq > ath9k_hw_fbin2freq(powInfo[i - 1].bChannel,
						IS_CHAN_2GHZ(chan))) {
				lowIndex = i - 1;
				break;
			}
		}
		if ((matchIndex == -1) && (lowIndex == -1))
			matchIndex = i - 1;
	}

	if (matchIndex != -1) {
		*pNewPower = powInfo[matchIndex];
	} else {
		clo = ath9k_hw_fbin2freq(powInfo[lowIndex].bChannel,
					 IS_CHAN_2GHZ(chan));
		chi = ath9k_hw_fbin2freq(powInfo[lowIndex + 1].bChannel,
					 IS_CHAN_2GHZ(chan));

		for (i = 0; i < numRates; i++) {
			pNewPower->tPow2x[i] =
				(u8)ath9k_hw_interpolate(freq, clo, chi,
						powInfo[lowIndex].tPow2x[i],
						powInfo[lowIndex + 1].tPow2x[i]);
		}
	}
}
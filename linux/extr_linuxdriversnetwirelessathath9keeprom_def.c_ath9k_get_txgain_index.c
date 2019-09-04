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
typedef  size_t u16 ;
struct chan_centers {int /*<<< orphan*/  synth_center; } ;
struct calDataPerFreqOpLoop {scalar_t__** pcdac; scalar_t__** pwrPdg; } ;
struct ath_hw {scalar_t__* originalGain; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR5416_BCHAN_UNUSED ; 
 int AR9280_TX_GAIN_TABLE_SIZE ; 
 scalar_t__ FREQ2FBIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_get_channel_centers (struct ath_hw*,struct ath9k_channel*,struct chan_centers*) ; 
 int ath9k_hw_get_lower_upper_index (scalar_t__,scalar_t__*,size_t,size_t*,size_t*) ; 

__attribute__((used)) static void ath9k_get_txgain_index(struct ath_hw *ah,
		struct ath9k_channel *chan,
		struct calDataPerFreqOpLoop *rawDatasetOpLoop,
		u8 *calChans,  u16 availPiers, u8 *pwr, u8 *pcdacIdx)
{
	u8 pcdac, i = 0;
	u16 idxL = 0, idxR = 0, numPiers;
	bool match;
	struct chan_centers centers;

	ath9k_hw_get_channel_centers(ah, chan, &centers);

	for (numPiers = 0; numPiers < availPiers; numPiers++)
		if (calChans[numPiers] == AR5416_BCHAN_UNUSED)
			break;

	match = ath9k_hw_get_lower_upper_index(
			(u8)FREQ2FBIN(centers.synth_center, IS_CHAN_2GHZ(chan)),
			calChans, numPiers, &idxL, &idxR);
	if (match) {
		pcdac = rawDatasetOpLoop[idxL].pcdac[0][0];
		*pwr = rawDatasetOpLoop[idxL].pwrPdg[0][0];
	} else {
		pcdac = rawDatasetOpLoop[idxR].pcdac[0][0];
		*pwr = (rawDatasetOpLoop[idxL].pwrPdg[0][0] +
				rawDatasetOpLoop[idxR].pwrPdg[0][0])/2;
	}

	while (pcdac > ah->originalGain[i] &&
			i < (AR9280_TX_GAIN_TABLE_SIZE - 1))
		i++;

	*pcdacIdx = i;
}
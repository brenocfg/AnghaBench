#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {scalar_t__* spurChans; } ;
struct TYPE_5__ {scalar_t__* spurChans; } ;
struct ar9300_eeprom {TYPE_3__ modalHeader2G; TYPE_2__ modalHeader5G; } ;
struct TYPE_4__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
struct ath9k_channel {int channel; } ;

/* Variables and functions */
 unsigned int AR_EEPROM_MODAL_SPURS ; 
 int /*<<< orphan*/  AR_PHY_GC_DYN2040_PRI_CH ; 
 int /*<<< orphan*/  AR_PHY_GEN_CTRL ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 scalar_t__ IS_CHAN_5GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int abs (int) ; 
 int /*<<< orphan*/  ar9003_hw_spur_ofdm_9565 (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_hw_spur_ofdm_clear (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_spur_ofdm_work (struct ath_hw*,struct ath9k_channel*,int,int,int) ; 
 int ath9k_hw_fbin2freq (scalar_t__,int) ; 

__attribute__((used)) static void ar9003_hw_spur_mitigate_ofdm(struct ath_hw *ah,
					 struct ath9k_channel *chan)
{
	int synth_freq;
	int range = 10;
	int freq_offset = 0;
	int mode;
	u8* spurChansPtr;
	unsigned int i;
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	if (IS_CHAN_5GHZ(chan)) {
		spurChansPtr = &(eep->modalHeader5G.spurChans[0]);
		mode = 0;
	}
	else {
		spurChansPtr = &(eep->modalHeader2G.spurChans[0]);
		mode = 1;
	}

	if (spurChansPtr[0] == 0)
		return; /* No spur in the mode */

	if (IS_CHAN_HT40(chan)) {
		range = 19;
		if (REG_READ_FIELD(ah, AR_PHY_GEN_CTRL,
				   AR_PHY_GC_DYN2040_PRI_CH) == 0x0)
			synth_freq = chan->channel - 10;
		else
			synth_freq = chan->channel + 10;
	} else {
		range = 10;
		synth_freq = chan->channel;
	}

	ar9003_hw_spur_ofdm_clear(ah);

	for (i = 0; i < AR_EEPROM_MODAL_SPURS && spurChansPtr[i]; i++) {
		freq_offset = ath9k_hw_fbin2freq(spurChansPtr[i], mode);
		freq_offset -= synth_freq;
		if (abs(freq_offset) < range) {
			ar9003_hw_spur_ofdm_work(ah, chan, freq_offset,
						 range, synth_freq);

			if (AR_SREV_9565(ah) && (i < 4)) {
				freq_offset = ath9k_hw_fbin2freq(spurChansPtr[i + 1],
								 mode);
				freq_offset -= synth_freq;
				if (abs(freq_offset) < range)
					ar9003_hw_spur_ofdm_9565(ah, freq_offset);
			}

			break;
		}
	}
}
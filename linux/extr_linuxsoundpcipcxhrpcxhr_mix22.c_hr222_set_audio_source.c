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
struct snd_pcxhr {scalar_t__ audio_capture_source; int analog_capture_active; int mic_active; TYPE_1__* mgr; } ;
struct TYPE_2__ {int xlx_cfg; scalar_t__ board_has_aes1; } ;

/* Variables and functions */
 int PCXHR_CFG_DATAIN_SEL_MASK ; 
 int PCXHR_CFG_DATA_UER1_SEL_MASK ; 
 int PCXHR_CFG_SRC_MASK ; 
 int /*<<< orphan*/  PCXHR_OUTPB (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCXHR_XLX_CFG ; 
 scalar_t__ SOURCE_DIGISRC ; 
 scalar_t__ SOURCE_DIGITAL ; 
 scalar_t__ SOURCE_LINE ; 
 scalar_t__ SOURCE_LINEMIC ; 
 scalar_t__ SOURCE_MIC ; 
 int /*<<< orphan*/  hr222_update_analog_audio_level (struct snd_pcxhr*,int,int /*<<< orphan*/ ) ; 

int hr222_set_audio_source(struct snd_pcxhr *chip)
{
	int digital = 0;
	/* default analog source */
	chip->mgr->xlx_cfg &= ~(PCXHR_CFG_SRC_MASK |
				PCXHR_CFG_DATAIN_SEL_MASK |
				PCXHR_CFG_DATA_UER1_SEL_MASK);

	if (chip->audio_capture_source == SOURCE_DIGISRC) {
		chip->mgr->xlx_cfg |= PCXHR_CFG_SRC_MASK;
		digital = 1;
	} else {
		if (chip->audio_capture_source == SOURCE_DIGITAL)
			digital = 1;
	}
	if (digital) {
		chip->mgr->xlx_cfg |=  PCXHR_CFG_DATAIN_SEL_MASK;
		if (chip->mgr->board_has_aes1) {
			/* get data from the AES1 plug */
			chip->mgr->xlx_cfg |= PCXHR_CFG_DATA_UER1_SEL_MASK;
		}
		/* chip->mic_active = 0; */
		/* chip->analog_capture_active = 0; */
	} else {
		int update_lvl = 0;
		chip->analog_capture_active = 0;
		chip->mic_active = 0;
		if (chip->audio_capture_source == SOURCE_LINE ||
		    chip->audio_capture_source == SOURCE_LINEMIC) {
			if (chip->analog_capture_active == 0)
				update_lvl = 1;
			chip->analog_capture_active = 1;
		}
		if (chip->audio_capture_source == SOURCE_MIC ||
		    chip->audio_capture_source == SOURCE_LINEMIC) {
			if (chip->mic_active == 0)
				update_lvl = 1;
			chip->mic_active = 1;
		}
		if (update_lvl) {
			/* capture: update all 3 mutes/unmutes with one call */
			hr222_update_analog_audio_level(chip, 1, 0);
		}
	}
	/* set the source infos (max 3 bits modified) */
	PCXHR_OUTPB(chip->mgr, PCXHR_XLX_CFG, chip->mgr->xlx_cfg);
	return 0;
}
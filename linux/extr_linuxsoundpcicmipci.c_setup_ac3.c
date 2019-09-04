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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct cmipci {int chip_version; scalar_t__ can_ac3_hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_AC3EN1 ; 
 int /*<<< orphan*/  CM_AC3EN2 ; 
 int /*<<< orphan*/  CM_PLAYBACK_SRATE_176K ; 
 int /*<<< orphan*/  CM_REG_CHFORMAT ; 
 int /*<<< orphan*/  CM_REG_MISC_CTRL ; 
 int /*<<< orphan*/  CM_SPD24SEL ; 
 int /*<<< orphan*/  CM_SPD32SEL ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cmipci_set_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_ac3(struct cmipci *cm, struct snd_pcm_substream *subs, int do_ac3, int rate)
{
	if (do_ac3) {
		/* AC3EN for 037 */
		snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_AC3EN1);
		/* AC3EN for 039 */
		snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_AC3EN2);
	
		if (cm->can_ac3_hw) {
			/* SPD24SEL for 037, 0x02 */
			/* SPD24SEL for 039, 0x20, but cannot be set */
			snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_SPD24SEL);
			snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
		} else { /* can_ac3_sw */
			/* SPD32SEL for 037 & 039, 0x20 */
			snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
			/* set 176K sample rate to fix 033 HW bug */
			if (cm->chip_version == 33) {
				if (rate >= 48000) {
					snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_PLAYBACK_SRATE_176K);
				} else {
					snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_PLAYBACK_SRATE_176K);
				}
			}
		}

	} else {
		snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_AC3EN1);
		snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_AC3EN2);

		if (cm->can_ac3_hw) {
			/* chip model >= 37 */
			if (snd_pcm_format_width(subs->runtime->format) > 16) {
				snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
				snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_SPD24SEL);
			} else {
				snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
				snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_SPD24SEL);
			}
		} else {
			snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_SPD24SEL);
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_PLAYBACK_SRATE_176K);
		}
	}
}
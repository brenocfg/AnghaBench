#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ substream; } ;
struct snd_cs46xx {int midcr; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  midi_output; int /*<<< orphan*/  midi_input; scalar_t__ rmidi; TYPE_2__ capt; scalar_t__ pcm; TYPE_1__* playback_pcm; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {scalar_t__ substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_HICR ; 
 int /*<<< orphan*/  BA0_HISR ; 
 int /*<<< orphan*/  BA0_MIDCR ; 
 int /*<<< orphan*/  BA0_MIDRP ; 
 int /*<<< orphan*/  BA0_MIDSR ; 
 int /*<<< orphan*/  BA0_MIDWP ; 
 unsigned char HICR_CHGM ; 
 unsigned char HICR_IEV ; 
 int HISR_MIDI ; 
 int HISR_VC0 ; 
 int HISR_VC1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MIDCR_RIE ; 
 int MIDCR_TIE ; 
 int MIDSR_RBE ; 
 int MIDSR_TBF ; 
 int snd_cs46xx_peekBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int snd_rawmidi_transmit (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_cs46xx_interrupt(int irq, void *dev_id)
{
	struct snd_cs46xx *chip = dev_id;
	u32 status1;
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	u32 status2;
	int i;
	struct snd_cs46xx_pcm *cpcm = NULL;
#endif

	/*
	 *  Read the Interrupt Status Register to clear the interrupt
	 */
	status1 = snd_cs46xx_peekBA0(chip, BA0_HISR);
	if ((status1 & 0x7fffffff) == 0) {
		snd_cs46xx_pokeBA0(chip, BA0_HICR, HICR_CHGM | HICR_IEV);
		return IRQ_NONE;
	}

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	status2 = snd_cs46xx_peekBA0(chip, BA0_HSR0);

	for (i = 0; i < DSP_MAX_PCM_CHANNELS; ++i) {
		if (i <= 15) {
			if ( status1 & (1 << i) ) {
				if (i == CS46XX_DSP_CAPTURE_CHANNEL) {
					if (chip->capt.substream)
						snd_pcm_period_elapsed(chip->capt.substream);
				} else {
					if (ins->pcm_channels[i].active &&
					    ins->pcm_channels[i].private_data &&
					    !ins->pcm_channels[i].unlinked) {
						cpcm = ins->pcm_channels[i].private_data;
						snd_pcm_period_elapsed(cpcm->substream);
					}
				}
			}
		} else {
			if ( status2 & (1 << (i - 16))) {
				if (ins->pcm_channels[i].active && 
				    ins->pcm_channels[i].private_data &&
				    !ins->pcm_channels[i].unlinked) {
					cpcm = ins->pcm_channels[i].private_data;
					snd_pcm_period_elapsed(cpcm->substream);
				}
			}
		}
	}

#else
	/* old dsp */
	if ((status1 & HISR_VC0) && chip->playback_pcm) {
		if (chip->playback_pcm->substream)
			snd_pcm_period_elapsed(chip->playback_pcm->substream);
	}
	if ((status1 & HISR_VC1) && chip->pcm) {
		if (chip->capt.substream)
			snd_pcm_period_elapsed(chip->capt.substream);
	}
#endif

	if ((status1 & HISR_MIDI) && chip->rmidi) {
		unsigned char c;
		
		spin_lock(&chip->reg_lock);
		while ((snd_cs46xx_peekBA0(chip, BA0_MIDSR) & MIDSR_RBE) == 0) {
			c = snd_cs46xx_peekBA0(chip, BA0_MIDRP);
			if ((chip->midcr & MIDCR_RIE) == 0)
				continue;
			snd_rawmidi_receive(chip->midi_input, &c, 1);
		}
		while ((snd_cs46xx_peekBA0(chip, BA0_MIDSR) & MIDSR_TBF) == 0) {
			if ((chip->midcr & MIDCR_TIE) == 0)
				break;
			if (snd_rawmidi_transmit(chip->midi_output, &c, 1) != 1) {
				chip->midcr &= ~MIDCR_TIE;
				snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
				break;
			}
			snd_cs46xx_pokeBA0(chip, BA0_MIDWP, c);
		}
		spin_unlock(&chip->reg_lock);
	}
	/*
	 *  EOI to the PCI part....reenables interrupts
	 */
	snd_cs46xx_pokeBA0(chip, BA0_HICR, HICR_CHGM | HICR_IEV);

	return IRQ_HANDLED;
}
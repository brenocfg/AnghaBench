#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int period_size; int /*<<< orphan*/  rate; int /*<<< orphan*/  format; struct snd_cs46xx_pcm* private_data; } ;
struct TYPE_7__ {unsigned int addr; } ;
struct TYPE_8__ {int hw_buffer_size; int /*<<< orphan*/  sw_buffer_size; } ;
struct snd_cs46xx_pcm {int shift; TYPE_3__ hw_buf; TYPE_2__* pcm_channel; TYPE_4__ pcm_rec; } ;
struct snd_cs46xx {int dummy; } ;
struct TYPE_6__ {unsigned int pcm_slot; TYPE_1__* pcm_reader_scb; } ;
struct TYPE_5__ {int address; } ;

/* Variables and functions */
 int BA1_PBA ; 
 int BA1_PDTC ; 
 int BA1_PFIE ; 
 int CS46XX_FRAGS ; 
 int ENXIO ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 unsigned int snd_cs46xx_peek (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int,unsigned int) ; 
 int /*<<< orphan*/  snd_cs46xx_set_play_sample_rate (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_format_big_endian (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_format_unsigned (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct snd_cs46xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cs46xx_playback_prepare(struct snd_pcm_substream *substream)
{
	unsigned int tmp;
	unsigned int pfie;
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_cs46xx_pcm *cpcm;

	cpcm = runtime->private_data;

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	if (snd_BUG_ON(!cpcm->pcm_channel))
		return -ENXIO;

	pfie = snd_cs46xx_peek(chip, (cpcm->pcm_channel->pcm_reader_scb->address + 1) << 2 );
	pfie &= ~0x0000f03f;
#else
	/* old dsp */
	pfie = snd_cs46xx_peek(chip, BA1_PFIE);
 	pfie &= ~0x0000f03f;
#endif

	cpcm->shift = 2;
	/* if to convert from stereo to mono */
	if (runtime->channels == 1) {
		cpcm->shift--;
		pfie |= 0x00002000;
	}
	/* if to convert from 8 bit to 16 bit */
	if (snd_pcm_format_width(runtime->format) == 8) {
		cpcm->shift--;
		pfie |= 0x00001000;
	}
	/* if to convert to unsigned */
	if (snd_pcm_format_unsigned(runtime->format))
		pfie |= 0x00008000;

	/* Never convert byte order when sample stream is 8 bit */
	if (snd_pcm_format_width(runtime->format) != 8) {
		/* convert from big endian to little endian */
		if (snd_pcm_format_big_endian(runtime->format))
			pfie |= 0x00004000;
	}
	
	memset(&cpcm->pcm_rec, 0, sizeof(cpcm->pcm_rec));
	cpcm->pcm_rec.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	cpcm->pcm_rec.hw_buffer_size = runtime->period_size * CS46XX_FRAGS << cpcm->shift;

#ifdef CONFIG_SND_CS46XX_NEW_DSP

	tmp = snd_cs46xx_peek(chip, (cpcm->pcm_channel->pcm_reader_scb->address) << 2);
	tmp &= ~0x000003ff;
	tmp |= (4 << cpcm->shift) - 1;
	/* playback transaction count register */
	snd_cs46xx_poke(chip, (cpcm->pcm_channel->pcm_reader_scb->address) << 2, tmp);

	/* playback format && interrupt enable */
	snd_cs46xx_poke(chip, (cpcm->pcm_channel->pcm_reader_scb->address + 1) << 2, pfie | cpcm->pcm_channel->pcm_slot);
#else
	snd_cs46xx_poke(chip, BA1_PBA, cpcm->hw_buf.addr);
	tmp = snd_cs46xx_peek(chip, BA1_PDTC);
	tmp &= ~0x000003ff;
	tmp |= (4 << cpcm->shift) - 1;
	snd_cs46xx_poke(chip, BA1_PDTC, tmp);
	snd_cs46xx_poke(chip, BA1_PFIE, pfie);
	snd_cs46xx_set_play_sample_rate(chip, runtime->rate);
#endif

	return 0;
}
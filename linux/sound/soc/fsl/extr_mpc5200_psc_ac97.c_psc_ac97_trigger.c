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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {TYPE_1__* pstr; } ;
struct psc_dma_stream {int /*<<< orphan*/  ac97_slot_bits; } ;
struct psc_dma {int /*<<< orphan*/  slots; TYPE_2__* psc_regs; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  ac97_slots; } ;
struct TYPE_3__ {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct psc_dma* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 struct psc_dma_stream* to_psc_dma_stream (struct snd_pcm_substream*,struct psc_dma*) ; 

__attribute__((used)) static int psc_ac97_trigger(struct snd_pcm_substream *substream, int cmd,
							struct snd_soc_dai *dai)
{
	struct psc_dma *psc_dma = snd_soc_dai_get_drvdata(dai);
	struct psc_dma_stream *s = to_psc_dma_stream(substream, psc_dma);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		dev_dbg(psc_dma->dev, "AC97 START: stream=%i\n",
			substream->pstr->stream);

		/* Set the slot enable bits */
		psc_dma->slots |= s->ac97_slot_bits;
		out_be32(&psc_dma->psc_regs->ac97_slots, psc_dma->slots);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
		dev_dbg(psc_dma->dev, "AC97 STOP: stream=%i\n",
			substream->pstr->stream);

		/* Clear the slot enable bits */
		psc_dma->slots &= ~(s->ac97_slot_bits);
		out_be32(&psc_dma->psc_regs->ac97_slots, psc_dma->slots);
		break;
	}
	return 0;
}
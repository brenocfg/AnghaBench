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
struct snd_pcm_substream {int dummy; } ;
struct atmel_ac97c {int opened; scalar_t__ regs; } ;

/* Variables and functions */
 unsigned long AC97C_CMR_CENA ; 
 unsigned long AC97C_CSR_ENDTX ; 
 scalar_t__ ATMEL_PDC_PTCR ; 
 unsigned long ATMEL_PDC_TXTDIS ; 
 unsigned long ATMEL_PDC_TXTEN ; 
 int /*<<< orphan*/  CAMR ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 unsigned long ac97c_readl (struct atmel_ac97c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97c_writel (struct atmel_ac97c*,int /*<<< orphan*/ ,unsigned long) ; 
 struct atmel_ac97c* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int
atmel_ac97c_playback_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct atmel_ac97c *chip = snd_pcm_substream_chip(substream);
	unsigned long camr, ptcr = 0;

	camr = ac97c_readl(chip, CAMR);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE: /* fall through */
	case SNDRV_PCM_TRIGGER_RESUME: /* fall through */
	case SNDRV_PCM_TRIGGER_START:
		ptcr = ATMEL_PDC_TXTEN;
		camr |= AC97C_CMR_CENA | AC97C_CSR_ENDTX;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH: /* fall through */
	case SNDRV_PCM_TRIGGER_SUSPEND: /* fall through */
	case SNDRV_PCM_TRIGGER_STOP:
		ptcr |= ATMEL_PDC_TXTDIS;
		if (chip->opened <= 1)
			camr &= ~AC97C_CMR_CENA;
		break;
	default:
		return -EINVAL;
	}

	ac97c_writel(chip, CAMR, camr);
	writel(ptcr, chip->regs + ATMEL_PDC_PTCR);
	return 0;
}
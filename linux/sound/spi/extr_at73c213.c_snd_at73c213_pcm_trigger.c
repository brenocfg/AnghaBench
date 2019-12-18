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
struct snd_pcm_substream {int dummy; } ;
struct snd_at73c213 {int /*<<< orphan*/  lock; TYPE_2__* spi; TYPE_1__* ssc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IDR ; 
 int /*<<< orphan*/  IDR_ENDTX ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  IER_ENDTX ; 
 int /*<<< orphan*/  PDC_PTCR ; 
 int /*<<< orphan*/  PDC_PTCR_TXTDIS ; 
 int /*<<< orphan*/  PDC_PTCR_TXTEN ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  SSC_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct snd_at73c213* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_at73c213_pcm_trigger(struct snd_pcm_substream *substream,
				   int cmd)
{
	struct snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	int retval = 0;

	spin_lock(&chip->lock);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		ssc_writel(chip->ssc->regs, IER, SSC_BIT(IER_ENDTX));
		ssc_writel(chip->ssc->regs, PDC_PTCR, SSC_BIT(PDC_PTCR_TXTEN));
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		ssc_writel(chip->ssc->regs, PDC_PTCR, SSC_BIT(PDC_PTCR_TXTDIS));
		ssc_writel(chip->ssc->regs, IDR, SSC_BIT(IDR_ENDTX));
		break;
	default:
		dev_dbg(&chip->spi->dev, "spurious command %x\n", cmd);
		retval = -EINVAL;
		break;
	}

	spin_unlock(&chip->lock);

	return retval;
}
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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_6__ {int /*<<< orphan*/  formats; int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {struct atiixp_dma* private_data; TYPE_3__ hw; } ;
struct atiixp_dma {int opened; int ac97_pcm_type; TYPE_2__* ops; struct snd_pcm_substream* substream; } ;
struct atiixp {int /*<<< orphan*/  reg_lock; TYPE_1__** pcms; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* enable_dma ) (struct atiixp*,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  rates; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 scalar_t__ snd_BUG_ON (int) ; 
 TYPE_3__ snd_atiixp_pcm_hw ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_limit_hw_rates (struct snd_pcm_runtime*) ; 
 struct atiixp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct atiixp*,int) ; 

__attribute__((used)) static int snd_atiixp_pcm_open(struct snd_pcm_substream *substream,
			       struct atiixp_dma *dma, int pcm_type)
{
	struct atiixp *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	if (snd_BUG_ON(!dma->ops || !dma->ops->enable_dma))
		return -EINVAL;

	if (dma->opened)
		return -EBUSY;
	dma->substream = substream;
	runtime->hw = snd_atiixp_pcm_hw;
	dma->ac97_pcm_type = pcm_type;
	if (pcm_type >= 0) {
		runtime->hw.rates = chip->pcms[pcm_type]->rates;
		snd_pcm_limit_hw_rates(runtime);
	} else {
		/* direct SPDIF */
		runtime->hw.formats = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE;
	}
	if ((err = snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		return err;
	runtime->private_data = dma;

	/* enable DMA bits */
	spin_lock_irq(&chip->reg_lock);
	dma->ops->enable_dma(chip, 1);
	spin_unlock_irq(&chip->reg_lock);
	dma->opened = 1;

	return 0;
}
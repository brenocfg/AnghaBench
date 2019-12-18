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
struct stm32_sai_sub_data {int /*<<< orphan*/  irq_lock; scalar_t__ substream; int /*<<< orphan*/  regmap; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ snd_pcm_state_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SAI_XCLRFR_MASK ; 
 unsigned int SAI_XIMR_AFSDETIE ; 
 unsigned int SAI_XIMR_CNRDYIE ; 
 unsigned int SAI_XIMR_LFSDETIE ; 
 unsigned int SAI_XIMR_MUTEDETIE ; 
 unsigned int SAI_XIMR_OVRUDRIE ; 
 unsigned int SAI_XIMR_WCKCFGIE ; 
 scalar_t__ SNDRV_PCM_STATE_DISCONNECTED ; 
 scalar_t__ SNDRV_PCM_STATE_RUNNING ; 
 scalar_t__ SNDRV_PCM_STATE_XRUN ; 
 int /*<<< orphan*/  STM_SAI_CLRFR_REGX ; 
 int /*<<< orphan*/  STM_SAI_IMR_REGX ; 
 scalar_t__ STM_SAI_IS_PLAYBACK (struct stm32_sai_sub_data*) ; 
 int /*<<< orphan*/  STM_SAI_SR_REGX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t stm32_sai_isr(int irq, void *devid)
{
	struct stm32_sai_sub_data *sai = (struct stm32_sai_sub_data *)devid;
	struct platform_device *pdev = sai->pdev;
	unsigned int sr, imr, flags;
	snd_pcm_state_t status = SNDRV_PCM_STATE_RUNNING;

	regmap_read(sai->regmap, STM_SAI_IMR_REGX, &imr);
	regmap_read(sai->regmap, STM_SAI_SR_REGX, &sr);

	flags = sr & imr;
	if (!flags)
		return IRQ_NONE;

	regmap_write_bits(sai->regmap, STM_SAI_CLRFR_REGX, SAI_XCLRFR_MASK,
			  SAI_XCLRFR_MASK);

	if (!sai->substream) {
		dev_err(&pdev->dev, "Device stopped. Spurious IRQ 0x%x\n", sr);
		return IRQ_NONE;
	}

	if (flags & SAI_XIMR_OVRUDRIE) {
		dev_err(&pdev->dev, "IRQ %s\n",
			STM_SAI_IS_PLAYBACK(sai) ? "underrun" : "overrun");
		status = SNDRV_PCM_STATE_XRUN;
	}

	if (flags & SAI_XIMR_MUTEDETIE)
		dev_dbg(&pdev->dev, "IRQ mute detected\n");

	if (flags & SAI_XIMR_WCKCFGIE) {
		dev_err(&pdev->dev, "IRQ wrong clock configuration\n");
		status = SNDRV_PCM_STATE_DISCONNECTED;
	}

	if (flags & SAI_XIMR_CNRDYIE)
		dev_err(&pdev->dev, "IRQ Codec not ready\n");

	if (flags & SAI_XIMR_AFSDETIE) {
		dev_err(&pdev->dev, "IRQ Anticipated frame synchro\n");
		status = SNDRV_PCM_STATE_XRUN;
	}

	if (flags & SAI_XIMR_LFSDETIE) {
		dev_err(&pdev->dev, "IRQ Late frame synchro\n");
		status = SNDRV_PCM_STATE_XRUN;
	}

	spin_lock(&sai->irq_lock);
	if (status != SNDRV_PCM_STATE_RUNNING && sai->substream)
		snd_pcm_stop_xrun(sai->substream);
	spin_unlock(&sai->irq_lock);

	return IRQ_HANDLED;
}
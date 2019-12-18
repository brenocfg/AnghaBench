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
struct snd_pcm_runtime {int periods; int dma_addr; int /*<<< orphan*/  period_size; } ;
struct atmel_ac97c {int playback_period; int capture_period; TYPE_1__* pdev; TYPE_2__* capture_substream; scalar_t__ regs; TYPE_2__* playback_substream; } ;
typedef  scalar_t__ irqreturn_t ;
struct TYPE_4__ {struct snd_pcm_runtime* runtime; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AC97C_CSR_ENDRX ; 
 int AC97C_CSR_ENDTX ; 
 int AC97C_CSR_OVRUN ; 
 int AC97C_CSR_RXRDY ; 
 int AC97C_CSR_TXEMPTY ; 
 int AC97C_CSR_TXRDY ; 
 int AC97C_CSR_UNRUN ; 
 int AC97C_SR_CAEVT ; 
 int AC97C_SR_COEVT ; 
 scalar_t__ ATMEL_PDC_RNCR ; 
 scalar_t__ ATMEL_PDC_RNPR ; 
 scalar_t__ ATMEL_PDC_TNCR ; 
 scalar_t__ ATMEL_PDC_TNPR ; 
 int /*<<< orphan*/  CAMR ; 
 int /*<<< orphan*/  CASR ; 
 int /*<<< orphan*/  COSR ; 
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 int /*<<< orphan*/  SR ; 
 int ac97c_readl (struct atmel_ac97c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*) ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (TYPE_2__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t atmel_ac97c_interrupt(int irq, void *dev)
{
	struct atmel_ac97c	*chip  = (struct atmel_ac97c *)dev;
	irqreturn_t		retval = IRQ_NONE;
	u32			sr     = ac97c_readl(chip, SR);
	u32			casr   = ac97c_readl(chip, CASR);
	u32			cosr   = ac97c_readl(chip, COSR);
	u32			camr   = ac97c_readl(chip, CAMR);

	if (sr & AC97C_SR_CAEVT) {
		struct snd_pcm_runtime *runtime;
		int offset, next_period, block_size;
		dev_dbg(&chip->pdev->dev, "channel A event%s%s%s%s%s%s\n",
				casr & AC97C_CSR_OVRUN   ? " OVRUN"   : "",
				casr & AC97C_CSR_RXRDY   ? " RXRDY"   : "",
				casr & AC97C_CSR_UNRUN   ? " UNRUN"   : "",
				casr & AC97C_CSR_TXEMPTY ? " TXEMPTY" : "",
				casr & AC97C_CSR_TXRDY   ? " TXRDY"   : "",
				!casr                    ? " NONE"    : "");
		if ((casr & camr) & AC97C_CSR_ENDTX) {
			runtime = chip->playback_substream->runtime;
			block_size = frames_to_bytes(runtime, runtime->period_size);
			chip->playback_period++;

			if (chip->playback_period == runtime->periods)
				chip->playback_period = 0;
			next_period = chip->playback_period + 1;
			if (next_period == runtime->periods)
				next_period = 0;

			offset = block_size * next_period;

			writel(runtime->dma_addr + offset, chip->regs + ATMEL_PDC_TNPR);
			writel(block_size / 2, chip->regs + ATMEL_PDC_TNCR);

			snd_pcm_period_elapsed(chip->playback_substream);
		}
		if ((casr & camr) & AC97C_CSR_ENDRX) {
			runtime = chip->capture_substream->runtime;
			block_size = frames_to_bytes(runtime, runtime->period_size);
			chip->capture_period++;

			if (chip->capture_period == runtime->periods)
				chip->capture_period = 0;
			next_period = chip->capture_period + 1;
			if (next_period == runtime->periods)
				next_period = 0;

			offset = block_size * next_period;

			writel(runtime->dma_addr + offset, chip->regs + ATMEL_PDC_RNPR);
			writel(block_size / 2, chip->regs + ATMEL_PDC_RNCR);
			snd_pcm_period_elapsed(chip->capture_substream);
		}
		retval = IRQ_HANDLED;
	}

	if (sr & AC97C_SR_COEVT) {
		dev_info(&chip->pdev->dev, "codec channel event%s%s%s%s%s\n",
				cosr & AC97C_CSR_OVRUN   ? " OVRUN"   : "",
				cosr & AC97C_CSR_RXRDY   ? " RXRDY"   : "",
				cosr & AC97C_CSR_TXEMPTY ? " TXEMPTY" : "",
				cosr & AC97C_CSR_TXRDY   ? " TXRDY"   : "",
				!cosr                    ? " NONE"    : "");
		retval = IRQ_HANDLED;
	}

	if (retval == IRQ_NONE) {
		dev_err(&chip->pdev->dev, "spurious interrupt sr 0x%08x "
				"casr 0x%08x cosr 0x%08x\n", sr, casr, cosr);
	}

	return retval;
}
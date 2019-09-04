#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* card; TYPE_3__* rmidi; int /*<<< orphan*/  irq; int /*<<< orphan*/  mmio; int /*<<< orphan*/  lock; TYPE_2__* dma_wt; TYPE_1__* dma_adb; } ;
typedef  TYPE_5__ vortex_t ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  private_data; } ;
struct TYPE_9__ {scalar_t__ fifo_status; int /*<<< orphan*/  substream; } ;
struct TYPE_8__ {scalar_t__ fifo_status; int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 int CTRL_IRQ_ENABLE ; 
 scalar_t__ FIFO_START ; 
 int IRQ_DMA ; 
 int IRQ_ERR_MASK ; 
 int IRQ_FATAL ; 
 int IRQ_FIFO ; 
 int IRQ_MIDI ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int IRQ_PARITY ; 
 int IRQ_PCMOUT ; 
 int IRQ_REG ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int IRQ_TIMER ; 
 int NR_ADB ; 
 int NR_WT ; 
 int /*<<< orphan*/  VORTEX_CTRL ; 
 int /*<<< orphan*/  VORTEX_IRQ_SOURCE ; 
 int /*<<< orphan*/  VORTEX_IRQ_STAT ; 
 int /*<<< orphan*/  VORTEX_STAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int hwread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vortex_adbdma_bufshift (TYPE_5__*,int) ; 
 int /*<<< orphan*/  vortex_wtdma_bufshift (TYPE_5__*,int) ; 

__attribute__((used)) static irqreturn_t vortex_interrupt(int irq, void *dev_id)
{
	vortex_t *vortex = dev_id;
	int i, handled;
	u32 source;

	//check if the interrupt is ours.
	if (!(hwread(vortex->mmio, VORTEX_STAT) & 0x1))
		return IRQ_NONE;

	// This is the Interrupt Enable flag we set before (consistency check).
	if (!(hwread(vortex->mmio, VORTEX_CTRL) & CTRL_IRQ_ENABLE))
		return IRQ_NONE;

	source = hwread(vortex->mmio, VORTEX_IRQ_SOURCE);
	// Reset IRQ flags.
	hwwrite(vortex->mmio, VORTEX_IRQ_SOURCE, source);
	hwread(vortex->mmio, VORTEX_IRQ_SOURCE);
	// Is at least one IRQ flag set?
	if (source == 0) {
		dev_err(vortex->card->dev, "missing irq source\n");
		return IRQ_NONE;
	}

	handled = 0;
	// Attend every interrupt source.
	if (unlikely(source & IRQ_ERR_MASK)) {
		if (source & IRQ_FATAL) {
			dev_err(vortex->card->dev, "IRQ fatal error\n");
		}
		if (source & IRQ_PARITY) {
			dev_err(vortex->card->dev, "IRQ parity error\n");
		}
		if (source & IRQ_REG) {
			dev_err(vortex->card->dev, "IRQ reg error\n");
		}
		if (source & IRQ_FIFO) {
			dev_err(vortex->card->dev, "IRQ fifo error\n");
		}
		if (source & IRQ_DMA) {
			dev_err(vortex->card->dev, "IRQ dma error\n");
		}
		handled = 1;
	}
	if (source & IRQ_PCMOUT) {
		/* ALSA period acknowledge. */
		spin_lock(&vortex->lock);
		for (i = 0; i < NR_ADB; i++) {
			if (vortex->dma_adb[i].fifo_status == FIFO_START) {
				if (!vortex_adbdma_bufshift(vortex, i))
					continue;
				spin_unlock(&vortex->lock);
				snd_pcm_period_elapsed(vortex->dma_adb[i].
						       substream);
				spin_lock(&vortex->lock);
			}
		}
#ifndef CHIP_AU8810
		for (i = 0; i < NR_WT; i++) {
			if (vortex->dma_wt[i].fifo_status == FIFO_START) {
				/* FIXME: we ignore the return value from
				 * vortex_wtdma_bufshift() below as the delta
				 * calculation seems not working for wavetable
				 * by some reason
				 */
				vortex_wtdma_bufshift(vortex, i);
				spin_unlock(&vortex->lock);
				snd_pcm_period_elapsed(vortex->dma_wt[i].
						       substream);
				spin_lock(&vortex->lock);
			}
		}
#endif
		spin_unlock(&vortex->lock);
		handled = 1;
	}
	//Acknowledge the Timer interrupt
	if (source & IRQ_TIMER) {
		hwread(vortex->mmio, VORTEX_IRQ_STAT);
		handled = 1;
	}
	if ((source & IRQ_MIDI) && vortex->rmidi) {
		snd_mpu401_uart_interrupt(vortex->irq,
					  vortex->rmidi->private_data);
		handled = 1;
	}

	if (!handled) {
		dev_err(vortex->card->dev, "unknown irq source %x\n", source);
	}
	return IRQ_RETVAL(handled);
}
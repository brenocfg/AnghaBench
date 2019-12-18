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
typedef  unsigned int u32 ;
struct snd_pcm_runtime {int period_size; int rate; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct hdac_stream {unsigned int stream_tag; unsigned int bufsize; int period_wallclk; int /*<<< orphan*/  delay_negative_threshold; scalar_t__ fifo_size; TYPE_2__ bdl; scalar_t__ frags; scalar_t__ format_val; TYPE_1__* substream; struct hdac_bus* bus; } ;
struct TYPE_6__ {scalar_t__ addr; } ;
struct hdac_bus {TYPE_3__ posbuf; scalar_t__ use_posbuf; int /*<<< orphan*/  snoop; } ;
struct TYPE_4__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 unsigned int AZX_DPLBASE_ENABLE ; 
 int /*<<< orphan*/  DPLBASE ; 
 int /*<<< orphan*/  SD_BDLPL ; 
 int /*<<< orphan*/  SD_BDLPU ; 
 int /*<<< orphan*/  SD_CBL ; 
 int /*<<< orphan*/  SD_CTL ; 
 unsigned int SD_CTL_STREAM_TAG_MASK ; 
 unsigned int SD_CTL_STREAM_TAG_SHIFT ; 
 unsigned int SD_CTL_TRAFFIC_PRIO ; 
 int /*<<< orphan*/  SD_FIFOSIZE ; 
 int /*<<< orphan*/  SD_FORMAT ; 
 int /*<<< orphan*/  SD_INT_MASK ; 
 int /*<<< orphan*/  SD_LVI ; 
 int /*<<< orphan*/  frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 unsigned int snd_hdac_chip_readl (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_writel (struct hdac_bus*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_hdac_stream_clear (struct hdac_stream*) ; 
 unsigned int snd_hdac_stream_readl (struct hdac_stream*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hdac_stream_readw (struct hdac_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_stream_updatel (struct hdac_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_stream_writel (struct hdac_stream*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_hdac_stream_writew (struct hdac_stream*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int upper_32_bits (scalar_t__) ; 

int snd_hdac_stream_setup(struct hdac_stream *azx_dev)
{
	struct hdac_bus *bus = azx_dev->bus;
	struct snd_pcm_runtime *runtime;
	unsigned int val;

	if (azx_dev->substream)
		runtime = azx_dev->substream->runtime;
	else
		runtime = NULL;
	/* make sure the run bit is zero for SD */
	snd_hdac_stream_clear(azx_dev);
	/* program the stream_tag */
	val = snd_hdac_stream_readl(azx_dev, SD_CTL);
	val = (val & ~SD_CTL_STREAM_TAG_MASK) |
		(azx_dev->stream_tag << SD_CTL_STREAM_TAG_SHIFT);
	if (!bus->snoop)
		val |= SD_CTL_TRAFFIC_PRIO;
	snd_hdac_stream_writel(azx_dev, SD_CTL, val);

	/* program the length of samples in cyclic buffer */
	snd_hdac_stream_writel(azx_dev, SD_CBL, azx_dev->bufsize);

	/* program the stream format */
	/* this value needs to be the same as the one programmed */
	snd_hdac_stream_writew(azx_dev, SD_FORMAT, azx_dev->format_val);

	/* program the stream LVI (last valid index) of the BDL */
	snd_hdac_stream_writew(azx_dev, SD_LVI, azx_dev->frags - 1);

	/* program the BDL address */
	/* lower BDL address */
	snd_hdac_stream_writel(azx_dev, SD_BDLPL, (u32)azx_dev->bdl.addr);
	/* upper BDL address */
	snd_hdac_stream_writel(azx_dev, SD_BDLPU,
			       upper_32_bits(azx_dev->bdl.addr));

	/* enable the position buffer */
	if (bus->use_posbuf && bus->posbuf.addr) {
		if (!(snd_hdac_chip_readl(bus, DPLBASE) & AZX_DPLBASE_ENABLE))
			snd_hdac_chip_writel(bus, DPLBASE,
				(u32)bus->posbuf.addr | AZX_DPLBASE_ENABLE);
	}

	/* set the interrupt enable bits in the descriptor control register */
	snd_hdac_stream_updatel(azx_dev, SD_CTL, 0, SD_INT_MASK);

	azx_dev->fifo_size = snd_hdac_stream_readw(azx_dev, SD_FIFOSIZE) + 1;

	/* when LPIB delay correction gives a small negative value,
	 * we ignore it; currently set the threshold statically to
	 * 64 frames
	 */
	if (runtime && runtime->period_size > 64)
		azx_dev->delay_negative_threshold =
			-frames_to_bytes(runtime, 64);
	else
		azx_dev->delay_negative_threshold = 0;

	/* wallclk has 24Mhz clock source */
	if (runtime)
		azx_dev->period_wallclk = (((runtime->period_size * 24000) /
				    runtime->rate) * 1000);

	return 0;
}
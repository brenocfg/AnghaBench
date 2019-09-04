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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct atiixp_dma* private_data; } ;
struct atiixp_modem {scalar_t__ remap_addr; TYPE_1__* card; } ;
struct atiixp_dma {unsigned int buf_addr; unsigned int buf_bytes; TYPE_2__* ops; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_4__ {scalar_t__ dt_cur; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 
 struct atiixp_modem* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_atiixp_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct atiixp_dma *dma = runtime->private_data;
	unsigned int curptr;
	int timeout = 1000;

	while (timeout--) {
		curptr = readl(chip->remap_addr + dma->ops->dt_cur);
		if (curptr < dma->buf_addr)
			continue;
		curptr -= dma->buf_addr;
		if (curptr >= dma->buf_bytes)
			continue;
		return bytes_to_frames(runtime, curptr);
	}
	dev_dbg(chip->card->dev, "invalid DMA pointer read 0x%x (buf=%x)\n",
		   readl(chip->remap_addr + dma->ops->dt_cur), dma->buf_addr);
	return 0;
}
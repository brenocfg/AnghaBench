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
struct snd_pcm_substream {TYPE_1__* pcm; TYPE_3__* runtime; } ;
struct snd_azf3328_codec_data {int /*<<< orphan*/  name; scalar_t__ dma_base; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_6__ {struct snd_azf3328_codec_data* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_2__* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDX_IO_CODEC_DMA_CURRPOS ; 
 int /*<<< orphan*/  IDX_IO_CODEC_DMA_START_1 ; 
 int /*<<< orphan*/  bytes_to_frames (TYPE_3__*,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned long snd_azf3328_codec_inl (struct snd_azf3328_codec_data const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_azf3328_pcm_pointer(struct snd_pcm_substream *substream
)
{
	const struct snd_azf3328_codec_data *codec =
		substream->runtime->private_data;
	unsigned long result;
	snd_pcm_uframes_t frmres;

	result = snd_azf3328_codec_inl(codec, IDX_IO_CODEC_DMA_CURRPOS);

	/* calculate offset */
#ifdef QUERY_HARDWARE
	result -= snd_azf3328_codec_inl(codec, IDX_IO_CODEC_DMA_START_1);
#else
	result -= codec->dma_base;
#endif
	frmres = bytes_to_frames( substream->runtime, result);
	dev_dbg(substream->pcm->card->dev, "%08li %s @ 0x%8lx, frames %8ld\n",
		jiffies, codec->name, result, frmres);
	return frmres;
}
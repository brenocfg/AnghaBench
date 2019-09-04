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
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  type; } ;
struct snd_dma_buffer {scalar_t__ bytes; TYPE_1__ dev; } ;
struct snd_pcm_substream {TYPE_3__* pcm; int /*<<< orphan*/  number; scalar_t__ stream; struct snd_dma_buffer dma_buffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  device; TYPE_2__* card; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,struct snd_dma_buffer*) ; 
 size_t snd_minimum_buffer ; 

__attribute__((used)) static int preallocate_pcm_pages(struct snd_pcm_substream *substream, size_t size)
{
	struct snd_dma_buffer *dmab = &substream->dma_buffer;
	size_t orig_size = size;
	int err;

	do {
		if ((err = snd_dma_alloc_pages(dmab->dev.type, dmab->dev.dev,
					       size, dmab)) < 0) {
			if (err != -ENOMEM)
				return err; /* fatal error */
		} else
			return 0;
		size >>= 1;
	} while (size >= snd_minimum_buffer);
	dmab->bytes = 0; /* tell error */
	pr_warn("ALSA pcmC%dD%d%c,%d:%s: cannot preallocate for size %zu\n",
		substream->pcm->card->number, substream->pcm->device,
		substream->stream ? 'c' : 'p', substream->number,
		substream->pcm->name, orig_size);
	return 0;
}
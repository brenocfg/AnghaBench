#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_intelhad {int dummy; } ;
struct TYPE_2__ {int dma_bytes; int /*<<< orphan*/ * dma_area; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  had_do_reset (struct snd_intelhad*) ; 
 int /*<<< orphan*/  set_memory_wb (unsigned long,int) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_intelhad* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int had_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_intelhad *intelhaddata;
	unsigned long addr;
	u32 pages;

	intelhaddata = snd_pcm_substream_chip(substream);
	had_do_reset(intelhaddata);

	/* mark back the pages as cached/writeback region before the free */
	if (substream->runtime->dma_area != NULL) {
		addr = (unsigned long) substream->runtime->dma_area;
		pages = (substream->runtime->dma_bytes + PAGE_SIZE - 1) /
								PAGE_SIZE;
		set_memory_wb(addr, pages);
		return snd_pcm_lib_free_pages(substream);
	}
	return 0;
}
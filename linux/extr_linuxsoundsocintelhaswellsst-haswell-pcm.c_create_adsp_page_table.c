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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int stream; } ;
struct snd_dma_buffer {int dummy; } ;
struct hsw_priv_data {TYPE_1__** dmab; } ;
struct TYPE_2__ {scalar_t__ area; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct snd_dma_buffer* snd_pcm_get_dma_buf (struct snd_pcm_substream*) ; 
 int snd_sgbuf_aligned_pages (size_t) ; 
 int snd_sgbuf_get_addr (struct snd_dma_buffer*,int) ; 

__attribute__((used)) static int create_adsp_page_table(struct snd_pcm_substream *substream,
	struct hsw_priv_data *pdata, struct snd_soc_pcm_runtime *rtd,
	unsigned char *dma_area, size_t size, int pcm)
{
	struct snd_dma_buffer *dmab = snd_pcm_get_dma_buf(substream);
	int i, pages, stream = substream->stream;

	pages = snd_sgbuf_aligned_pages(size);

	dev_dbg(rtd->dev, "generating page table for %p size 0x%zx pages %d\n",
		dma_area, size, pages);

	for (i = 0; i < pages; i++) {
		u32 idx = (((i << 2) + i)) >> 1;
		u32 pfn = snd_sgbuf_get_addr(dmab, i * PAGE_SIZE) >> PAGE_SHIFT;
		u32 *pg_table;

		dev_dbg(rtd->dev, "pfn i %i idx %d pfn %x\n", i, idx, pfn);

		pg_table = (u32 *)(pdata->dmab[pcm][stream].area + idx);

		if (i & 1)
			*pg_table |= (pfn << 4);
		else
			*pg_table |= pfn;
	}

	return 0;
}
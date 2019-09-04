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
struct snd_sg_buf {TYPE_1__* table; } ;
struct snd_dma_buffer {struct snd_sg_buf* private_data; } ;
struct TYPE_2__ {unsigned int addr; } ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 

unsigned int snd_sgbuf_get_chunk_size(struct snd_dma_buffer *dmab,
				      unsigned int ofs, unsigned int size)
{
	struct snd_sg_buf *sg = dmab->private_data;
	unsigned int start, end, pg;

	start = ofs >> PAGE_SHIFT;
	end = (ofs + size - 1) >> PAGE_SHIFT;
	/* check page continuity */
	pg = sg->table[start].addr >> PAGE_SHIFT;
	for (;;) {
		start++;
		if (start > end)
			break;
		pg++;
		if ((sg->table[start].addr >> PAGE_SHIFT) != pg)
			return (start << PAGE_SHIFT) - ofs;
	}
	/* ok, all on continuous pages */
	return size;
}
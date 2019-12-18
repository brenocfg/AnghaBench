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
typedef  int u8 ;
typedef  int u32 ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct snd_dma_buffer {int /*<<< orphan*/  area; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int*) ; 
 int snd_sgbuf_aligned_pages (size_t) ; 
 int snd_sgbuf_get_addr (struct snd_dma_buffer*,int) ; 

int snd_sof_create_page_table(struct snd_sof_dev *sdev,
			      struct snd_dma_buffer *dmab,
			      unsigned char *page_table, size_t size)
{
	int i, pages;

	pages = snd_sgbuf_aligned_pages(size);

	dev_dbg(sdev->dev, "generating page table for %p size 0x%zx pages %d\n",
		dmab->area, size, pages);

	for (i = 0; i < pages; i++) {
		/*
		 * The number of valid address bits for each page is 20.
		 * idx determines the byte position within page_table
		 * where the current page's address is stored
		 * in the compressed page_table.
		 * This can be calculated by multiplying the page number by 2.5.
		 */
		u32 idx = (5 * i) >> 1;
		u32 pfn = snd_sgbuf_get_addr(dmab, i * PAGE_SIZE) >> PAGE_SHIFT;
		u8 *pg_table;

		dev_vdbg(sdev->dev, "pfn i %i idx %d pfn %x\n", i, idx, pfn);

		pg_table = (u8 *)(page_table + idx);

		/*
		 * pagetable compression:
		 * byte 0     byte 1     byte 2     byte 3     byte 4     byte 5
		 * ___________pfn 0__________ __________pfn 1___________  _pfn 2...
		 * .... ....  .... ....  .... ....  .... ....  .... ....  ....
		 * It is created by:
		 * 1. set current location to 0, PFN index i to 0
		 * 2. put pfn[i] at current location in Little Endian byte order
		 * 3. calculate an intermediate value as
		 *    x = (pfn[i+1] << 4) | (pfn[i] & 0xf)
		 * 4. put x at offset (current location + 2) in LE byte order
		 * 5. increment current location by 5 bytes, increment i by 2
		 * 6. continue to (2)
		 */
		if (i & 1)
			put_unaligned_le32((pg_table[0] & 0xf) | pfn << 4,
					   pg_table);
		else
			put_unaligned_le32(pfn, pg_table);
	}

	return pages;
}
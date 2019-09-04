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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/ * area; } ;
struct viadev {unsigned int tbl_entries; unsigned int bufsize; int bufsize2; TYPE_2__* idx_table; TYPE_1__ table; } ;
struct via82xx_modem {int /*<<< orphan*/  pci; } ;
struct snd_pcm_substream {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {unsigned int offset; unsigned int size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_ALIGN (int) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int VIA_TABLE_SIZE ; 
 unsigned int VIA_TBL_BIT_EOL ; 
 unsigned int VIA_TBL_BIT_FLAG ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 unsigned int snd_pcm_sgbuf_get_addr (struct snd_pcm_substream*,unsigned int) ; 
 struct via82xx_modem* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int build_via_table(struct viadev *dev, struct snd_pcm_substream *substream,
			   struct pci_dev *pci,
			   unsigned int periods, unsigned int fragsize)
{
	unsigned int i, idx, ofs, rest;
	struct via82xx_modem *chip = snd_pcm_substream_chip(substream);

	if (dev->table.area == NULL) {
		/* the start of each lists must be aligned to 8 bytes,
		 * but the kernel pages are much bigger, so we don't care
		 */
		if (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, snd_dma_pci_data(chip->pci),
					PAGE_ALIGN(VIA_TABLE_SIZE * 2 * 8),
					&dev->table) < 0)
			return -ENOMEM;
	}
	if (! dev->idx_table) {
		dev->idx_table = kmalloc_array(VIA_TABLE_SIZE,
					       sizeof(*dev->idx_table),
					       GFP_KERNEL);
		if (! dev->idx_table)
			return -ENOMEM;
	}

	/* fill the entries */
	idx = 0;
	ofs = 0;
	for (i = 0; i < periods; i++) {
		rest = fragsize;
		/* fill descriptors for a period.
		 * a period can be split to several descriptors if it's
		 * over page boundary.
		 */
		do {
			unsigned int r;
			unsigned int flag;
			unsigned int addr;

			if (idx >= VIA_TABLE_SIZE) {
				dev_err(&pci->dev, "too much table size!\n");
				return -EINVAL;
			}
			addr = snd_pcm_sgbuf_get_addr(substream, ofs);
			((u32 *)dev->table.area)[idx << 1] = cpu_to_le32(addr);
			r = PAGE_SIZE - (ofs % PAGE_SIZE);
			if (rest < r)
				r = rest;
			rest -= r;
			if (! rest) {
				if (i == periods - 1)
					flag = VIA_TBL_BIT_EOL; /* buffer boundary */
				else
					flag = VIA_TBL_BIT_FLAG; /* period boundary */
			} else
				flag = 0; /* period continues to the next */
			/*
			dev_dbg(&pci->dev,
				"tbl %d: at %d  size %d (rest %d)\n",
				idx, ofs, r, rest);
			*/
			((u32 *)dev->table.area)[(idx<<1) + 1] = cpu_to_le32(r | flag);
			dev->idx_table[idx].offset = ofs;
			dev->idx_table[idx].size = r;
			ofs += r;
			idx++;
		} while (rest > 0);
	}
	dev->tbl_entries = idx;
	dev->bufsize = periods * fragsize;
	dev->bufsize2 = dev->bufsize / 2;
	return 0;
}
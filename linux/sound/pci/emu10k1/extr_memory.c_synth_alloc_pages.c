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
struct snd_emu10k1_memblk {int dummy; } ;
struct snd_emu10k1 {int /*<<< orphan*/ * page_ptr_table; int /*<<< orphan*/ * page_addr_table; int /*<<< orphan*/  memhdr; } ;
struct snd_dma_buffer {int /*<<< orphan*/  area; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __synth_free_pages (struct snd_emu10k1*,int,int) ; 
 int /*<<< orphan*/  emu10k1_memblk_init (struct snd_emu10k1_memblk*) ; 
 int /*<<< orphan*/  get_single_page_range (int /*<<< orphan*/ ,struct snd_emu10k1_memblk*,int*,int*) ; 
 int /*<<< orphan*/  is_valid_page (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (struct snd_dma_buffer*) ; 
 scalar_t__ snd_emu10k1_alloc_pages_maybe_wider (struct snd_emu10k1*,int /*<<< orphan*/ ,struct snd_dma_buffer*) ; 

__attribute__((used)) static int synth_alloc_pages(struct snd_emu10k1 *emu, struct snd_emu10k1_memblk *blk)
{
	int page, first_page, last_page;
	struct snd_dma_buffer dmab;

	emu10k1_memblk_init(blk);
	get_single_page_range(emu->memhdr, blk, &first_page, &last_page);
	/* allocate kernel pages */
	for (page = first_page; page <= last_page; page++) {
		if (snd_emu10k1_alloc_pages_maybe_wider(emu, PAGE_SIZE,
							&dmab) < 0)
			goto __fail;
		if (!is_valid_page(emu, dmab.addr)) {
			snd_dma_free_pages(&dmab);
			goto __fail;
		}
		emu->page_addr_table[page] = dmab.addr;
		emu->page_ptr_table[page] = dmab.area;
	}
	return 0;

__fail:
	/* release allocated pages */
	last_page = page - 1;
	__synth_free_pages(emu, first_page, last_page);

	return -ENOMEM;
}
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
struct snd_emu10k1 {TYPE_1__* card; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ EMUPAGESIZE ; 
 int UNIT_PAGES ; 
 scalar_t__ __get_ptb_entry (struct snd_emu10k1*,int) ; 
 int /*<<< orphan*/  __set_ptb_entry (struct snd_emu10k1*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 

__attribute__((used)) static inline void set_ptb_entry(struct snd_emu10k1 *emu, int page, dma_addr_t addr)
{
	int i;
	page *= UNIT_PAGES;
	for (i = 0; i < UNIT_PAGES; i++, page++) {
		__set_ptb_entry(emu, page, addr);
		dev_dbg(emu->card->dev, "mapped page %d to entry %.8x\n", page,
			(unsigned int)__get_ptb_entry(emu, page));
		addr += EMUPAGESIZE;
	}
}
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
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct snd_emu10k1 {TYPE_2__* card; TYPE_1__ silent_page; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int UNIT_PAGES ; 
 scalar_t__ __get_ptb_entry (struct snd_emu10k1*,int) ; 
 int /*<<< orphan*/  __set_ptb_entry (struct snd_emu10k1*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 

__attribute__((used)) static inline void set_silent_ptb(struct snd_emu10k1 *emu, int page)
{
	int i;
	page *= UNIT_PAGES;
	for (i = 0; i < UNIT_PAGES; i++, page++) {
		/* do not increment ptr */
		__set_ptb_entry(emu, page, emu->silent_page.addr);
		dev_dbg(emu->card->dev, "mapped silent page %d to entry %.8x\n",
			page, (unsigned int)__get_ptb_entry(emu, page));
	}
}
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
struct TYPE_4__ {TYPE_1__* idx; } ;
struct snd_cs46xx {TYPE_2__ region; } ;
struct TYPE_3__ {scalar_t__ remap_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void snd_cs46xx_poke(struct snd_cs46xx *chip, unsigned long reg, unsigned int val)
{
	unsigned int bank = reg >> 16;
	unsigned int offset = reg & 0xffff;

	/*
	if (bank == 0)
		printk(KERN_DEBUG "snd_cs46xx_poke: %04X - %08X\n",
		       reg >> 2,val);
	*/
	writel(val, chip->region.idx[bank+1].remap_addr + offset);
}
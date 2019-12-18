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
typedef  int u32 ;
struct esschan {int fmt; int* apu; int* wc_map; } ;
struct es1968 {int dummy; } ;

/* Variables and functions */
 int ESS_FMT_16BIT ; 
 int ESS_FMT_STEREO ; 
 int /*<<< orphan*/  wave_set_register (struct es1968*,int,int) ; 

__attribute__((used)) static void snd_es1968_program_wavecache(struct es1968 *chip, struct esschan *es,
					 int channel, u32 addr, int capture)
{
	u32 tmpval = (addr - 0x10) & 0xFFF8;

	if (! capture) {
		if (!(es->fmt & ESS_FMT_16BIT))
			tmpval |= 4;	/* 8bit */
		if (es->fmt & ESS_FMT_STEREO)
			tmpval |= 2;	/* stereo */
	}

	/* set the wavecache control reg */
	wave_set_register(chip, es->apu[channel] << 3, tmpval);

#ifdef CONFIG_PM_SLEEP
	es->wc_map[channel] = tmpval;
#endif
}
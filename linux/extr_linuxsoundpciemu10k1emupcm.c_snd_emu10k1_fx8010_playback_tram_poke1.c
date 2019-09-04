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

/* Variables and functions */

__attribute__((used)) static void snd_emu10k1_fx8010_playback_tram_poke1(unsigned short *dst_left,
						   unsigned short *dst_right,
						   unsigned short *src,
						   unsigned int count,
						   unsigned int tram_shift)
{
	/*
	dev_dbg(emu->card->dev,
		"tram_poke1: dst_left = 0x%p, dst_right = 0x%p, "
	       "src = 0x%p, count = 0x%x\n",
	       dst_left, dst_right, src, count);
	*/
	if ((tram_shift & 1) == 0) {
		while (count--) {
			*dst_left-- = *src++;
			*dst_right-- = *src++;
		}
	} else {
		while (count--) {
			*dst_right-- = *src++;
			*dst_left-- = *src++;
		}
	}
}
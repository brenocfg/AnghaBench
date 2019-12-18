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
struct esschan {int* apu; int* apu_mode; unsigned int* base; } ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct es1968 {TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  apu_set_register (struct es1968*,int,int,int) ; 
 int /*<<< orphan*/  snd_es1968_program_wavecache (struct es1968*,struct esschan*,int,unsigned int,int) ; 

__attribute__((used)) static void init_capture_apu(struct es1968 *chip, struct esschan *es, int channel,
			     unsigned int pa, unsigned int bsize,
			     int mode, int route)
{
	int i, apu = es->apu[channel];

	es->apu_mode[channel] = mode;

	/* set the wavecache control reg */
	snd_es1968_program_wavecache(chip, es, channel, pa, 1);

	/* Offset to PCMBAR */
	pa -= chip->dma.addr;
	pa >>= 1;	/* words */

	/* base offset of dma calcs when reading the pointer
	   on this left one */
	es->base[channel] = pa & 0xFFFF;
	pa |= 0x00400000;	/* bit 22 -> System RAM */

	/* Begin loading the APU */
	for (i = 0; i < 16; i++)
		apu_set_register(chip, apu, i, 0x0000);

	/* need to enable subgroups.. and we should probably
	   have different groups for different /dev/dsps..  */
	apu_set_register(chip, apu, 2, 0x8);

	/* Load the buffer into the wave engine */
	apu_set_register(chip, apu, 4, ((pa >> 16) & 0xFF) << 8);
	apu_set_register(chip, apu, 5, pa & 0xFFFF);
	apu_set_register(chip, apu, 6, (pa + bsize) & 0xFFFF);
	apu_set_register(chip, apu, 7, bsize);
	/* clear effects/env.. */
	apu_set_register(chip, apu, 8, 0x00F0);
	/* amplitude now?  sure.  why not.  */
	apu_set_register(chip, apu, 9, 0x0000);
	/* set filter tune, radius, polar pan */
	apu_set_register(chip, apu, 10, 0x8F08);
	/* route input */
	apu_set_register(chip, apu, 11, route);
	/* dma on, no envelopes, filter to all 1s) */
	apu_set_register(chip, apu, 0, 0x400F);
}
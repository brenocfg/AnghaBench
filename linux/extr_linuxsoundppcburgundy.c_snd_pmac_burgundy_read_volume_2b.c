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
struct snd_pmac {int dummy; } ;

/* Variables and functions */
 long BURGUNDY_VOLUME_OFFSET ; 
 long snd_pmac_burgundy_rcb (struct snd_pmac*,unsigned int) ; 

__attribute__((used)) static void
snd_pmac_burgundy_read_volume_2b(struct snd_pmac *chip, unsigned int address,
				 long *volume, int off)
{
	volume[0] = snd_pmac_burgundy_rcb(chip, address + off);
	if (volume[0] >= BURGUNDY_VOLUME_OFFSET)
		volume[0] -= BURGUNDY_VOLUME_OFFSET;
	else
		volume[0] = 0;
	volume[1] = snd_pmac_burgundy_rcb(chip, address + off + 0x100);
	if (volume[1] >= BURGUNDY_VOLUME_OFFSET)
		volume[1] -= BURGUNDY_VOLUME_OFFSET;
	else
		volume[1] = 0;
}
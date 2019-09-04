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
 int BURGUNDY_VOLUME_OFFSET ; 
 int /*<<< orphan*/  snd_pmac_burgundy_wcw (struct snd_pmac*,unsigned int,int) ; 

__attribute__((used)) static void
snd_pmac_burgundy_write_volume(struct snd_pmac *chip, unsigned int address,
			       long *volume, int shift)
{
	int hardvolume, lvolume, rvolume;

	if (volume[0] < 0 || volume[0] > 100 ||
	    volume[1] < 0 || volume[1] > 100)
		return; /* -EINVAL */
	lvolume = volume[0] ? volume[0] + BURGUNDY_VOLUME_OFFSET : 0;
	rvolume = volume[1] ? volume[1] + BURGUNDY_VOLUME_OFFSET : 0;

	hardvolume = lvolume + (rvolume << shift);
	if (shift == 8)
		hardvolume |= hardvolume << 16;

	snd_pmac_burgundy_wcw(chip, address, hardvolume);
}
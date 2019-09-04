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
struct snd_pmac {int* awacs_reg; int rate_index; } ;

/* Variables and functions */
 int MASK_SAMPLERATE ; 
 int /*<<< orphan*/  snd_pmac_awacs_write_reg (struct snd_pmac*,int,int) ; 

__attribute__((used)) static void snd_pmac_awacs_set_format(struct snd_pmac *chip)
{
	chip->awacs_reg[1] &= ~MASK_SAMPLERATE;
	chip->awacs_reg[1] |= chip->rate_index << 3;
	snd_pmac_awacs_write_reg(chip, 1, chip->awacs_reg[1]);
}
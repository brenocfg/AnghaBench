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
struct snd_pmac {int* awacs_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pmac_awacs_write (struct snd_pmac*,int) ; 

__attribute__((used)) static void
snd_pmac_awacs_write_reg(struct snd_pmac *chip, int reg, int val)
{
	snd_pmac_awacs_write(chip, val | (reg << 12));
	chip->awacs_reg[reg] = val;
}
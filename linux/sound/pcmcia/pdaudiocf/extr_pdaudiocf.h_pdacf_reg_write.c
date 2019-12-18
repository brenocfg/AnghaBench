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
struct snd_pdacf {unsigned short* regmap; scalar_t__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

__attribute__((used)) static inline void pdacf_reg_write(struct snd_pdacf *chip, unsigned char reg, unsigned short val)
{
	outw(chip->regmap[reg>>1] = val, chip->port + reg);
}
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
struct ak4114 {unsigned char* regmap; unsigned char* txcsb; } ;

/* Variables and functions */
 unsigned char AK4114_REG_INT1_MASK ; 
 unsigned char AK4114_REG_TXCSB0 ; 
 unsigned char AK4114_REG_TXCSB4 ; 
 int /*<<< orphan*/  reg_write (struct ak4114*,unsigned char,unsigned char) ; 

void snd_ak4114_reg_write(struct ak4114 *chip, unsigned char reg, unsigned char mask, unsigned char val)
{
	if (reg <= AK4114_REG_INT1_MASK)
		reg_write(chip, reg, (chip->regmap[reg] & ~mask) | val);
	else if (reg >= AK4114_REG_TXCSB0 && reg <= AK4114_REG_TXCSB4)
		reg_write(chip, reg,
			  (chip->txcsb[reg-AK4114_REG_TXCSB0] & ~mask) | val);
}
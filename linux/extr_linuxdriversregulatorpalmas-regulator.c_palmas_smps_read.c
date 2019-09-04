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
struct palmas {int /*<<< orphan*/ * regmap; } ;

/* Variables and functions */
 unsigned int PALMAS_BASE_TO_REG (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PALMAS_SMPS_BASE ; 
 size_t REGULATOR_SLAVE ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int palmas_smps_read(struct palmas *palmas, unsigned int reg,
		unsigned int *dest)
{
	unsigned int addr;

	addr = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE, reg);

	return regmap_read(palmas->regmap[REGULATOR_SLAVE], addr, dest);
}
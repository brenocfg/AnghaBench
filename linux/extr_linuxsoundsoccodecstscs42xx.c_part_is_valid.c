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
struct tscs42xx {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_DEVIDH ; 
 int /*<<< orphan*/  R_DEVIDL ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int part_is_valid(struct tscs42xx *tscs42xx)
{
	int val;
	int ret;
	unsigned int reg;

	ret = regmap_read(tscs42xx->regmap, R_DEVIDH, &reg);
	if (ret < 0)
		return ret;

	val = reg << 8;
	ret = regmap_read(tscs42xx->regmap, R_DEVIDL, &reg);
	if (ret < 0)
		return ret;

	val |= reg;

	switch (val) {
	case 0x4A74:
	case 0x4A73:
		return true;
	default:
		return false;
	};
}
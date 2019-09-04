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
struct regmap {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,unsigned int,int*) ; 

int rl6231_get_pre_div(struct regmap *map, unsigned int reg, int sft)
{
	int pd, val;

	regmap_read(map, reg, &val);

	val = (val >> sft) & 0x7;

	switch (val) {
	case 0:
	case 1:
	case 2:
	case 3:
		pd = val + 1;
		break;
	case 4:
		pd = 6;
		break;
	case 5:
		pd = 8;
		break;
	case 6:
		pd = 12;
		break;
	case 7:
		pd = 16;
		break;
	default:
		pd = -EINVAL;
		break;
	}

	return pd;
}
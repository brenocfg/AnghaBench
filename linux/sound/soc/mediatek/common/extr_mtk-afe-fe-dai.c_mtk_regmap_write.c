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
 int regmap_write (struct regmap*,int,unsigned int) ; 

__attribute__((used)) static int mtk_regmap_write(struct regmap *map, int reg, unsigned int val)
{
	if (reg < 0)
		return 0;
	return regmap_write(map, reg, val);
}
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
 unsigned int CHG_INT_OK_CHGIN_MASK ; 
 int /*<<< orphan*/  MAX77693_CHG_REG_CHG_INT_OK ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max77693_get_online(struct regmap *regmap, int *val)
{
	unsigned int data;
	int ret;

	ret = regmap_read(regmap, MAX77693_CHG_REG_CHG_INT_OK, &data);
	if (ret < 0)
		return ret;

	*val = (data & CHG_INT_OK_CHGIN_MASK) ? 1 : 0;

	return 0;
}
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
struct rt5640_priv {int ldo1_en; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5640_parse_dt(struct rt5640_priv *rt5640, struct device_node *np)
{
	rt5640->ldo1_en = of_get_named_gpio(np, "realtek,ldo1-en-gpios", 0);
	/*
	 * LDO1_EN is optional (it may be statically tied on the board).
	 * -ENOENT means that the property doesn't exist, i.e. there is no
	 * GPIO, so is not an error. Any other error code means the property
	 * exists, but could not be parsed.
	 */
	if (!gpio_is_valid(rt5640->ldo1_en) &&
			(rt5640->ldo1_en != -ENOENT))
		return rt5640->ldo1_en;

	return 0;
}
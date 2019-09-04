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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt8173_spec_pupd ; 
 int mtk_pctrl_spec_pull_set_samereg (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned char,int,unsigned int) ; 

__attribute__((used)) static int mt8173_spec_pull_set(struct regmap *regmap, unsigned int pin,
		unsigned char align, bool isup, unsigned int r1r0)
{
	return mtk_pctrl_spec_pull_set_samereg(regmap, mt8173_spec_pupd,
		ARRAY_SIZE(mt8173_spec_pupd), pin, align, isup, r1r0);
}
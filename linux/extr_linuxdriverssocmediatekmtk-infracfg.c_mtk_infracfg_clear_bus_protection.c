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
typedef  int u32 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFRA_TOPAXI_PROTECTEN ; 
 int /*<<< orphan*/  INFRA_TOPAXI_PROTECTEN_CLR ; 
 int /*<<< orphan*/  INFRA_TOPAXI_PROTECTSTA1 ; 
 int /*<<< orphan*/  MTK_POLL_DELAY_US ; 
 int /*<<< orphan*/  MTK_POLL_TIMEOUT ; 
 int regmap_read_poll_timeout (struct regmap*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

int mtk_infracfg_clear_bus_protection(struct regmap *infracfg, u32 mask,
		bool reg_update)
{
	int ret;
	u32 val;

	if (reg_update)
		regmap_update_bits(infracfg, INFRA_TOPAXI_PROTECTEN, mask, 0);
	else
		regmap_write(infracfg, INFRA_TOPAXI_PROTECTEN_CLR, mask);

	ret = regmap_read_poll_timeout(infracfg, INFRA_TOPAXI_PROTECTSTA1,
				       val, !(val & mask),
				       MTK_POLL_DELAY_US, MTK_POLL_TIMEOUT);

	return ret;
}
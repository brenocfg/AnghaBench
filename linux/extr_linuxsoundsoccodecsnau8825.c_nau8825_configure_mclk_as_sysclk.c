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
 int /*<<< orphan*/  NAU8825_CLK_SRC_MASK ; 
 int /*<<< orphan*/  NAU8825_CLK_SRC_MCLK ; 
 int /*<<< orphan*/  NAU8825_DCO_EN ; 
 int /*<<< orphan*/  NAU8825_ICTRL_LATCH_MASK ; 
 int /*<<< orphan*/  NAU8825_REG_CLK_DIVIDER ; 
 int /*<<< orphan*/  NAU8825_REG_FLL1 ; 
 int /*<<< orphan*/  NAU8825_REG_FLL6 ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nau8825_configure_mclk_as_sysclk(struct regmap *regmap)
{
	regmap_update_bits(regmap, NAU8825_REG_CLK_DIVIDER,
		NAU8825_CLK_SRC_MASK, NAU8825_CLK_SRC_MCLK);
	regmap_update_bits(regmap, NAU8825_REG_FLL6,
		NAU8825_DCO_EN, 0);
	/* Make DSP operate as default setting for power saving. */
	regmap_update_bits(regmap, NAU8825_REG_FLL1,
		NAU8825_ICTRL_LATCH_MASK, 0);
}
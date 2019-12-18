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
struct nau8824 {int /*<<< orphan*/  dev; struct regmap* regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HZ ; 
#define  NAU8824_CLK_DIS 133 
#define  NAU8824_CLK_FLL_BLK 132 
#define  NAU8824_CLK_FLL_FS 131 
#define  NAU8824_CLK_FLL_MCLK 130 
#define  NAU8824_CLK_INTERNAL 129 
#define  NAU8824_CLK_MCLK 128 
 int /*<<< orphan*/  NAU8824_CLK_SRC_MASK ; 
 int /*<<< orphan*/  NAU8824_CLK_SRC_MCLK ; 
 int /*<<< orphan*/  NAU8824_CLK_SRC_VCO ; 
 int /*<<< orphan*/  NAU8824_DCO_EN ; 
 int /*<<< orphan*/  NAU8824_FLL_CLK_SRC_BLK ; 
 int /*<<< orphan*/  NAU8824_FLL_CLK_SRC_FS ; 
 int /*<<< orphan*/  NAU8824_FLL_CLK_SRC_MASK ; 
 int /*<<< orphan*/  NAU8824_FLL_CLK_SRC_MCLK ; 
 int /*<<< orphan*/  NAU8824_REG_CLK_DIVIDER ; 
 int /*<<< orphan*/  NAU8824_REG_FLL3 ; 
 int /*<<< orphan*/  NAU8824_REG_FLL6 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nau8824_sema_acquire (struct nau8824*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nau8824_sema_release (struct nau8824*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nau8824_config_sysclk(struct nau8824 *nau8824,
	int clk_id, unsigned int freq)
{
	struct regmap *regmap = nau8824->regmap;

	switch (clk_id) {
	case NAU8824_CLK_DIS:
		regmap_update_bits(regmap, NAU8824_REG_CLK_DIVIDER,
			NAU8824_CLK_SRC_MASK, NAU8824_CLK_SRC_MCLK);
		regmap_update_bits(regmap, NAU8824_REG_FLL6,
			NAU8824_DCO_EN, 0);
		break;

	case NAU8824_CLK_MCLK:
		nau8824_sema_acquire(nau8824, HZ);
		regmap_update_bits(regmap, NAU8824_REG_CLK_DIVIDER,
			NAU8824_CLK_SRC_MASK, NAU8824_CLK_SRC_MCLK);
		regmap_update_bits(regmap, NAU8824_REG_FLL6,
			NAU8824_DCO_EN, 0);
		nau8824_sema_release(nau8824);
		break;

	case NAU8824_CLK_INTERNAL:
		regmap_update_bits(regmap, NAU8824_REG_FLL6,
			NAU8824_DCO_EN, NAU8824_DCO_EN);
		regmap_update_bits(regmap, NAU8824_REG_CLK_DIVIDER,
			NAU8824_CLK_SRC_MASK, NAU8824_CLK_SRC_VCO);
		break;

	case NAU8824_CLK_FLL_MCLK:
		nau8824_sema_acquire(nau8824, HZ);
		regmap_update_bits(regmap, NAU8824_REG_FLL3,
			NAU8824_FLL_CLK_SRC_MASK, NAU8824_FLL_CLK_SRC_MCLK);
		nau8824_sema_release(nau8824);
		break;

	case NAU8824_CLK_FLL_BLK:
		nau8824_sema_acquire(nau8824, HZ);
		regmap_update_bits(regmap, NAU8824_REG_FLL3,
			NAU8824_FLL_CLK_SRC_MASK, NAU8824_FLL_CLK_SRC_BLK);
		nau8824_sema_release(nau8824);
		break;

	case NAU8824_CLK_FLL_FS:
		nau8824_sema_acquire(nau8824, HZ);
		regmap_update_bits(regmap, NAU8824_REG_FLL3,
			NAU8824_FLL_CLK_SRC_MASK, NAU8824_FLL_CLK_SRC_FS);
		nau8824_sema_release(nau8824);
		break;

	default:
		dev_err(nau8824->dev, "Invalid clock id (%d)\n", clk_id);
		return -EINVAL;
	}

	dev_dbg(nau8824->dev, "Sysclk is %dHz and clock id is %d\n", freq,
		clk_id);

	return 0;
}
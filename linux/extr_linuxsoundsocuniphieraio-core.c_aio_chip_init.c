#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uniphier_aio_chip {TYPE_1__* chip_spec; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {scalar_t__ addr_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  A2AIOINPUTSEL ; 
 int A2AIOINPUTSEL_RXSEL_IECI1_HDMIRX1 ; 
 int /*<<< orphan*/  A2AIOINPUTSEL_RXSEL_MASK ; 
 int A2AIOINPUTSEL_RXSEL_PCMI1_HDMIRX1 ; 
 int A2AIOINPUTSEL_RXSEL_PCMI2_SIF ; 
 int A2AIOINPUTSEL_RXSEL_PCMI3_EVEA ; 
 int /*<<< orphan*/  A2APLLCTR0 ; 
 int /*<<< orphan*/  A2APLLCTR0_APLLXPOW_MASK ; 
 int A2APLLCTR0_APLLXPOW_PWON ; 
 int /*<<< orphan*/  A2EXMCLKSEL0 ; 
 int /*<<< orphan*/  A2EXMCLKSEL0_EXMCLK_MASK ; 
 int A2EXMCLKSEL0_EXMCLK_OUTPUT ; 
 int /*<<< orphan*/  CDA2D_TEST ; 
 int CDA2D_TEST_DDR_MODE_EXTOFF1 ; 
 int CDA2D_TEST_DDR_MODE_EXTON0 ; 
 int /*<<< orphan*/  CDA2D_TEST_DDR_MODE_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void aio_chip_init(struct uniphier_aio_chip *chip)
{
	struct regmap *r = chip->regmap;

	regmap_update_bits(r, A2APLLCTR0,
			   A2APLLCTR0_APLLXPOW_MASK,
			   A2APLLCTR0_APLLXPOW_PWON);

	regmap_update_bits(r, A2EXMCLKSEL0,
			   A2EXMCLKSEL0_EXMCLK_MASK,
			   A2EXMCLKSEL0_EXMCLK_OUTPUT);

	regmap_update_bits(r, A2AIOINPUTSEL, A2AIOINPUTSEL_RXSEL_MASK,
			   A2AIOINPUTSEL_RXSEL_PCMI1_HDMIRX1 |
			   A2AIOINPUTSEL_RXSEL_PCMI2_SIF |
			   A2AIOINPUTSEL_RXSEL_PCMI3_EVEA |
			   A2AIOINPUTSEL_RXSEL_IECI1_HDMIRX1);

	if (chip->chip_spec->addr_ext)
		regmap_update_bits(r, CDA2D_TEST, CDA2D_TEST_DDR_MODE_MASK,
				   CDA2D_TEST_DDR_MODE_EXTON0);
	else
		regmap_update_bits(r, CDA2D_TEST, CDA2D_TEST_DDR_MODE_MASK,
				   CDA2D_TEST_DDR_MODE_EXTOFF1);
}
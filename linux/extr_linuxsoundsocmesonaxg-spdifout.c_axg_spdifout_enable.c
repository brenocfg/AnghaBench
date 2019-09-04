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
 int /*<<< orphan*/  SPDIFOUT_CTRL0 ; 
 int SPDIFOUT_CTRL0_EN ; 
 int SPDIFOUT_CTRL0_RST_IN ; 
 int SPDIFOUT_CTRL0_RST_OUT ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void axg_spdifout_enable(struct regmap *map)
{
	/* Apply both reset */
	regmap_update_bits(map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_RST_OUT | SPDIFOUT_CTRL0_RST_IN,
			   0);

	/* Clear out reset before in reset */
	regmap_update_bits(map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_RST_OUT, SPDIFOUT_CTRL0_RST_OUT);
	regmap_update_bits(map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_RST_IN,  SPDIFOUT_CTRL0_RST_IN);

	/* Enable spdifout */
	regmap_update_bits(map, SPDIFOUT_CTRL0, SPDIFOUT_CTRL0_EN,
			   SPDIFOUT_CTRL0_EN);
}
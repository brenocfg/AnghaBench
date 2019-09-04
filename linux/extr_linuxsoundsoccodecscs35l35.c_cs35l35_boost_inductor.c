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
struct cs35l35_private {int /*<<< orphan*/  dev; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L35_BST_CONV_COEF_1 ; 
 int /*<<< orphan*/  CS35L35_BST_CONV_COEF_2 ; 
 int /*<<< orphan*/  CS35L35_BST_CONV_LBST_MASK ; 
 int /*<<< orphan*/  CS35L35_BST_CONV_SLOPE_COMP ; 
 int /*<<< orphan*/  CS35L35_BST_CONV_SWFREQ_MASK ; 
 int /*<<< orphan*/  CS35L35_BST_CONV_SW_FREQ ; 
 unsigned int CS35L35_BST_IPK_MASK ; 
 int /*<<< orphan*/  CS35L35_BST_PEAK_I ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cs35l35_boost_inductor(struct cs35l35_private *cs35l35,
				  int inductor)
{
	struct regmap *regmap = cs35l35->regmap;
	unsigned int bst_ipk = 0;

	/*
	 * Digital Boost Converter Configuration for feedback,
	 * ramping, switching frequency, and estimation block seeding.
	 */

	regmap_update_bits(regmap, CS35L35_BST_CONV_SW_FREQ,
			   CS35L35_BST_CONV_SWFREQ_MASK, 0x00);

	regmap_read(regmap, CS35L35_BST_PEAK_I, &bst_ipk);
	bst_ipk &= CS35L35_BST_IPK_MASK;

	switch (inductor) {
	case 1000: /* 1 uH */
		regmap_write(regmap, CS35L35_BST_CONV_COEF_1, 0x24);
		regmap_write(regmap, CS35L35_BST_CONV_COEF_2, 0x24);
		regmap_update_bits(regmap, CS35L35_BST_CONV_SW_FREQ,
				   CS35L35_BST_CONV_LBST_MASK, 0x00);

		if (bst_ipk < 0x04)
			regmap_write(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x1B);
		else
			regmap_write(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x4E);
		break;
	case 1200: /* 1.2 uH */
		regmap_write(regmap, CS35L35_BST_CONV_COEF_1, 0x20);
		regmap_write(regmap, CS35L35_BST_CONV_COEF_2, 0x20);
		regmap_update_bits(regmap, CS35L35_BST_CONV_SW_FREQ,
				   CS35L35_BST_CONV_LBST_MASK, 0x01);

		if (bst_ipk < 0x04)
			regmap_write(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x1B);
		else
			regmap_write(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x47);
		break;
	case 1500: /* 1.5uH */
		regmap_write(regmap, CS35L35_BST_CONV_COEF_1, 0x20);
		regmap_write(regmap, CS35L35_BST_CONV_COEF_2, 0x20);
		regmap_update_bits(regmap, CS35L35_BST_CONV_SW_FREQ,
				   CS35L35_BST_CONV_LBST_MASK, 0x02);

		if (bst_ipk < 0x04)
			regmap_write(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x1B);
		else
			regmap_write(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x3C);
		break;
	case 2200: /* 2.2uH */
		regmap_write(regmap, CS35L35_BST_CONV_COEF_1, 0x19);
		regmap_write(regmap, CS35L35_BST_CONV_COEF_2, 0x25);
		regmap_update_bits(regmap, CS35L35_BST_CONV_SW_FREQ,
				   CS35L35_BST_CONV_LBST_MASK, 0x03);

		if (bst_ipk < 0x04)
			regmap_write(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x1B);
		else
			regmap_write(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x23);
		break;
	default:
		dev_err(cs35l35->dev, "Invalid Inductor Value %d uH\n",
			inductor);
		return -EINVAL;
	}
	return 0;
}
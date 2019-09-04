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
typedef  int u8 ;
struct spmi_regulator {int logical_type; } ;
struct regulator_dev {int dummy; } ;
typedef  enum spmi_regulator_logical_type { ____Placeholder_spmi_regulator_logical_type } spmi_regulator_logical_type ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SPMI_BOOST_BYP_REG_CURRENT_LIMIT ; 
 int SPMI_BOOST_CURRENT_LIMIT_ENABLE_MASK ; 
 int SPMI_BOOST_CURRENT_LIMIT_MASK ; 
 unsigned int SPMI_BOOST_REG_CURRENT_LIMIT ; 
 int SPMI_REGULATOR_LOGICAL_TYPE_BOOST ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int spmi_vreg_update_bits (struct spmi_regulator*,unsigned int,int,int) ; 

__attribute__((used)) static int spmi_regulator_set_ilim(struct regulator_dev *rdev, int ilim_uA)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	enum spmi_regulator_logical_type type = vreg->logical_type;
	unsigned int current_reg;
	u8 reg;
	u8 mask = SPMI_BOOST_CURRENT_LIMIT_MASK |
		  SPMI_BOOST_CURRENT_LIMIT_ENABLE_MASK;
	int max = (SPMI_BOOST_CURRENT_LIMIT_MASK + 1) * 500;

	if (type == SPMI_REGULATOR_LOGICAL_TYPE_BOOST)
		current_reg = SPMI_BOOST_REG_CURRENT_LIMIT;
	else
		current_reg = SPMI_BOOST_BYP_REG_CURRENT_LIMIT;

	if (ilim_uA > max || ilim_uA <= 0)
		return -EINVAL;

	reg = (ilim_uA - 1) / 500;
	reg |= SPMI_BOOST_CURRENT_LIMIT_ENABLE_MASK;

	return spmi_vreg_update_bits(vreg, current_reg, reg, mask);
}
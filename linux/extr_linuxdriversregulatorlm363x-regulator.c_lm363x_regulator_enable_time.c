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
typedef  size_t u8 ;
struct regulator_dev {int /*<<< orphan*/  regmap; } ;
typedef  enum lm363x_regulator_id { ____Placeholder_lm363x_regulator_id } lm363x_regulator_id ;

/* Variables and functions */
 int EINVAL ; 
 size_t ENABLE_TIME_USEC ; 
 size_t LM3631_ENTIME_CONT_MASK ; 
 size_t LM3631_ENTIME_MASK ; 
 size_t LM3631_ENTIME_SHIFT ; 
#define  LM3631_LDO_CONT 131 
#define  LM3631_LDO_NEG 130 
#define  LM3631_LDO_OREF 129 
#define  LM3631_LDO_POS 128 
 size_t LM3631_REG_ENTIME_VCONT ; 
 size_t LM3631_REG_ENTIME_VNEG ; 
 size_t LM3631_REG_ENTIME_VOREF ; 
 size_t LM3631_REG_ENTIME_VPOS ; 
 int* ldo_cont_enable_time ; 
 int rdev_get_id (struct regulator_dev*) ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,size_t,unsigned int*) ; 

__attribute__((used)) static int lm363x_regulator_enable_time(struct regulator_dev *rdev)
{
	enum lm363x_regulator_id id = rdev_get_id(rdev);
	u8 val, addr, mask;

	switch (id) {
	case LM3631_LDO_CONT:
		addr = LM3631_REG_ENTIME_VCONT;
		mask = LM3631_ENTIME_CONT_MASK;
		break;
	case LM3631_LDO_OREF:
		addr = LM3631_REG_ENTIME_VOREF;
		mask = LM3631_ENTIME_MASK;
		break;
	case LM3631_LDO_POS:
		addr = LM3631_REG_ENTIME_VPOS;
		mask = LM3631_ENTIME_MASK;
		break;
	case LM3631_LDO_NEG:
		addr = LM3631_REG_ENTIME_VNEG;
		mask = LM3631_ENTIME_MASK;
		break;
	default:
		return 0;
	}

	if (regmap_read(rdev->regmap, addr, (unsigned int *)&val))
		return -EINVAL;

	val = (val & mask) >> LM3631_ENTIME_SHIFT;

	if (id == LM3631_LDO_CONT)
		return ldo_cont_enable_time[val];
	else
		return ENABLE_TIME_USEC * val;
}
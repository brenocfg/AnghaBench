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
struct ds1307 {int /*<<< orphan*/  regmap; int /*<<< orphan*/  flags; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HAS_ALARM ; 
 int /*<<< orphan*/  RX8130_REG_CONTROL0 ; 
 int RX8130_REG_CONTROL0_AIE ; 
 struct ds1307* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rx8130_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct ds1307 *ds1307 = dev_get_drvdata(dev);
	int ret, reg;

	if (!test_bit(HAS_ALARM, &ds1307->flags))
		return -EINVAL;

	ret = regmap_read(ds1307->regmap, RX8130_REG_CONTROL0, &reg);
	if (ret < 0)
		return ret;

	if (enabled)
		reg |= RX8130_REG_CONTROL0_AIE;
	else
		reg &= ~RX8130_REG_CONTROL0_AIE;

	return regmap_write(ds1307->regmap, RX8130_REG_CONTROL0, reg);
}
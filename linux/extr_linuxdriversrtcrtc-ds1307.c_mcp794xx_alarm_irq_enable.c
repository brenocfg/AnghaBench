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
 int /*<<< orphan*/  MCP794XX_BIT_ALM0_EN ; 
 int /*<<< orphan*/  MCP794XX_REG_CONTROL ; 
 struct ds1307* dev_get_drvdata (struct device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcp794xx_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct ds1307 *ds1307 = dev_get_drvdata(dev);

	if (!test_bit(HAS_ALARM, &ds1307->flags))
		return -EINVAL;

	return regmap_update_bits(ds1307->regmap, MCP794XX_REG_CONTROL,
				  MCP794XX_BIT_ALM0_EN,
				  enabled ? MCP794XX_BIT_ALM0_EN : 0);
}
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
struct ds3232 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS3232_REG_CR ; 
 int DS3232_REG_CR_A1IE ; 
 struct ds3232* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds3232_update_alarm(struct device *dev, unsigned int enabled)
{
	struct ds3232 *ds3232 = dev_get_drvdata(dev);
	int control;
	int ret;

	ret = regmap_read(ds3232->regmap, DS3232_REG_CR, &control);
	if (ret)
		return ret;

	if (enabled)
		/* enable alarm1 interrupt */
		control |= DS3232_REG_CR_A1IE;
	else
		/* disable alarm1 interrupt */
		control &= ~(DS3232_REG_CR_A1IE);
	ret = regmap_write(ds3232->regmap, DS3232_REG_CR, control);

	return ret;
}
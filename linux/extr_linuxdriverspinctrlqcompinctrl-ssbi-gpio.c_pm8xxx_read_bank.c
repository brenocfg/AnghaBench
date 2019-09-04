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
struct pm8xxx_pin_data {int /*<<< orphan*/  reg; } ;
struct pm8xxx_gpio {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pm8xxx_read_bank(struct pm8xxx_gpio *pctrl,
			    struct pm8xxx_pin_data *pin, int bank)
{
	unsigned int val = bank << 4;
	int ret;

	ret = regmap_write(pctrl->regmap, pin->reg, val);
	if (ret) {
		dev_err(pctrl->dev, "failed to select bank %d\n", bank);
		return ret;
	}

	ret = regmap_read(pctrl->regmap, pin->reg, &val);
	if (ret) {
		dev_err(pctrl->dev, "failed to read register %d\n", bank);
		return ret;
	}

	return val;
}
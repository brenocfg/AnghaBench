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
struct s2mps11_info {int* ext_control_gpio; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_regulator_match {int /*<<< orphan*/  name; int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 unsigned int S2MPS14_LDO10 ; 
 unsigned int S2MPS14_LDO11 ; 
 unsigned int S2MPS14_LDO12 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int of_get_named_gpio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s2mps14_pmic_dt_parse_ext_control_gpio(struct platform_device *pdev,
		struct of_regulator_match *rdata, struct s2mps11_info *s2mps11)
{
	int *gpio = s2mps11->ext_control_gpio;
	unsigned int i;
	unsigned int valid_regulators[3] = { S2MPS14_LDO10, S2MPS14_LDO11,
		S2MPS14_LDO12 };

	for (i = 0; i < ARRAY_SIZE(valid_regulators); i++) {
		unsigned int reg = valid_regulators[i];

		if (!rdata[reg].init_data || !rdata[reg].of_node)
			continue;

		gpio[reg] = of_get_named_gpio(rdata[reg].of_node,
				"samsung,ext-control-gpios", 0);
		if (gpio_is_valid(gpio[reg]))
			dev_dbg(&pdev->dev, "Using GPIO %d for ext-control over %d/%s\n",
					gpio[reg], reg, rdata[reg].name);
	}
}
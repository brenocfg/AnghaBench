#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {int number; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  aspeed_g4_pinctrl_data ; 
 int /*<<< orphan*/  aspeed_g4_pinctrl_desc ; 
 TYPE_1__* aspeed_g4_pins ; 
 int aspeed_pinctrl_probe (struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aspeed_g4_pinctrl_probe(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(aspeed_g4_pins); i++)
		aspeed_g4_pins[i].number = i;

	return aspeed_pinctrl_probe(pdev, &aspeed_g4_pinctrl_desc,
			&aspeed_g4_pinctrl_data);
}
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
struct arizona {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_IRQ_SPK_OVERHEAT ; 
 int /*<<< orphan*/  ARIZONA_IRQ_SPK_OVERHEAT_WARN ; 
 int arizona_request_irq (struct arizona*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct arizona*) ; 
 int /*<<< orphan*/  arizona_thermal_shutdown ; 
 int /*<<< orphan*/  arizona_thermal_warn ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

int arizona_init_spk_irqs(struct arizona *arizona)
{
	int ret;

	ret = arizona_request_irq(arizona, ARIZONA_IRQ_SPK_OVERHEAT_WARN,
				  "Thermal warning", arizona_thermal_warn,
				  arizona);
	if (ret != 0)
		dev_err(arizona->dev,
			"Failed to get thermal warning IRQ: %d\n",
			ret);

	ret = arizona_request_irq(arizona, ARIZONA_IRQ_SPK_OVERHEAT,
				  "Thermal shutdown", arizona_thermal_shutdown,
				  arizona);
	if (ret != 0)
		dev_err(arizona->dev,
			"Failed to get thermal shutdown IRQ: %d\n",
			ret);

	return 0;
}
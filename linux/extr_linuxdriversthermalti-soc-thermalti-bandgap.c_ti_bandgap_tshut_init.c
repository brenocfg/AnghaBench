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
struct ti_bandgap {int tshut_gpio; int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int gpio_request (int,char*) ; 
 int /*<<< orphan*/  gpio_to_irq (int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_bandgap_tshut_irq_handler ; 

__attribute__((used)) static int ti_bandgap_tshut_init(struct ti_bandgap *bgp,
				 struct platform_device *pdev)
{
	int gpio_nr = bgp->tshut_gpio;
	int status;

	/* Request for gpio_86 line */
	status = gpio_request(gpio_nr, "tshut");
	if (status < 0) {
		dev_err(bgp->dev, "Could not request for TSHUT GPIO:%i\n", 86);
		return status;
	}
	status = gpio_direction_input(gpio_nr);
	if (status) {
		dev_err(bgp->dev, "Cannot set input TSHUT GPIO %d\n", gpio_nr);
		return status;
	}

	status = request_irq(gpio_to_irq(gpio_nr), ti_bandgap_tshut_irq_handler,
			     IRQF_TRIGGER_RISING, "tshut", NULL);
	if (status) {
		gpio_free(gpio_nr);
		dev_err(bgp->dev, "request irq failed for TSHUT");
	}

	return 0;
}
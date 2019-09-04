#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct gpio_regulator_data {TYPE_1__ desc; int /*<<< orphan*/  gpios; int /*<<< orphan*/  states; int /*<<< orphan*/  nr_gpios; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct gpio_regulator_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_regulator_remove(struct platform_device *pdev)
{
	struct gpio_regulator_data *drvdata = platform_get_drvdata(pdev);

	regulator_unregister(drvdata->dev);

	gpio_free_array(drvdata->gpios, drvdata->nr_gpios);

	kfree(drvdata->states);
	kfree(drvdata->gpios);

	kfree(drvdata->desc.name);

	return 0;
}
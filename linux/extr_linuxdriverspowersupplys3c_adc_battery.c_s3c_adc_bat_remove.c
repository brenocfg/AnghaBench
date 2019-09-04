#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct s3c_adc_client {int dummy; } ;
struct s3c_adc_bat_pdata {scalar_t__ gpio_charge_finished; int /*<<< orphan*/  (* exit ) () ;scalar_t__ backup_volt_mult; } ;
struct TYPE_4__ {struct s3c_adc_bat_pdata* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  psy; } ;
struct TYPE_5__ {int /*<<< orphan*/  psy; } ;

/* Variables and functions */
 TYPE_3__ backup_bat ; 
 int /*<<< orphan*/  bat_work ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  gpio_to_irq (scalar_t__) ; 
 TYPE_2__ main_bat ; 
 struct s3c_adc_client* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_adc_release (struct s3c_adc_client*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int s3c_adc_bat_remove(struct platform_device *pdev)
{
	struct s3c_adc_client *client = platform_get_drvdata(pdev);
	struct s3c_adc_bat_pdata *pdata = pdev->dev.platform_data;

	power_supply_unregister(main_bat.psy);
	if (pdata->backup_volt_mult)
		power_supply_unregister(backup_bat.psy);

	s3c_adc_release(client);

	if (pdata->gpio_charge_finished >= 0) {
		free_irq(gpio_to_irq(pdata->gpio_charge_finished), NULL);
		gpio_free(pdata->gpio_charge_finished);
	}

	cancel_delayed_work(&bat_work);

	if (pdata->exit)
		pdata->exit();

	return 0;
}
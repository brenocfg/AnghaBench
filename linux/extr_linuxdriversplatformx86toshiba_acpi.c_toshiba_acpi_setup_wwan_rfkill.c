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
struct toshiba_acpi_dev {int /*<<< orphan*/  wwan_rfk; int /*<<< orphan*/  killswitch; TYPE_1__* acpi_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RFKILL_TYPE_WWAN ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rfkill_alloc (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct toshiba_acpi_dev*) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ ) ; 
 int rfkill_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 
 int toshiba_wireless_status (struct toshiba_acpi_dev*) ; 
 int /*<<< orphan*/  wwan_rfk_ops ; 

__attribute__((used)) static int toshiba_acpi_setup_wwan_rfkill(struct toshiba_acpi_dev *dev)
{
	int ret = toshiba_wireless_status(dev);

	if (ret)
		return ret;

	dev->wwan_rfk = rfkill_alloc("Toshiba WWAN",
				     &dev->acpi_dev->dev,
				     RFKILL_TYPE_WWAN,
				     &wwan_rfk_ops,
				     dev);
	if (!dev->wwan_rfk) {
		pr_err("Unable to allocate WWAN rfkill device\n");
		return -ENOMEM;
	}

	rfkill_set_hw_state(dev->wwan_rfk, !dev->killswitch);

	ret = rfkill_register(dev->wwan_rfk);
	if (ret) {
		pr_err("Unable to register WWAN rfkill device\n");
		rfkill_destroy(dev->wwan_rfk);
	}

	return ret;
}
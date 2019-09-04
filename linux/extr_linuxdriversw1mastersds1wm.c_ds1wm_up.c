#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ds1wm_driver_data {int /*<<< orphan*/  clock_rate; } ;
struct ds1wm_data {TYPE_2__* pdev; TYPE_1__* cell; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DS1WM_CLKDIV ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ds1wm_driver_data* dev_get_platdata (struct device*) ; 
 int ds1wm_find_divisor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1wm_reset (struct ds1wm_data*) ; 
 int /*<<< orphan*/  ds1wm_write_register (struct ds1wm_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void ds1wm_up(struct ds1wm_data *ds1wm_data)
{
	int divisor;
	struct device *dev = &ds1wm_data->pdev->dev;
	struct ds1wm_driver_data *plat = dev_get_platdata(dev);

	if (ds1wm_data->cell->enable)
		ds1wm_data->cell->enable(ds1wm_data->pdev);

	divisor = ds1wm_find_divisor(plat->clock_rate);
	dev_dbg(dev, "found divisor 0x%x for clock %d\n",
		divisor, plat->clock_rate);
	if (divisor == 0) {
		dev_err(dev, "no suitable divisor for %dHz clock\n",
			plat->clock_rate);
		return;
	}
	ds1wm_write_register(ds1wm_data, DS1WM_CLKDIV, divisor);

	/* Let the w1 clock stabilize. */
	msleep(1);

	ds1wm_reset(ds1wm_data);
}
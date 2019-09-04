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
struct gasket_driver_desc {int num_page_tables; int /*<<< orphan*/  device_status_cb; } ;
struct gasket_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * page_table; TYPE_1__* internal_desc; } ;
struct TYPE_2__ {struct gasket_driver_desc* driver_desc; } ;

/* Variables and functions */
 int GASKET_STATUS_ALIVE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int gasket_check_and_invoke_callback_nolock (struct gasket_dev*,int /*<<< orphan*/ ) ; 
 int gasket_interrupt_system_status (struct gasket_dev*) ; 
 int gasket_page_table_system_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gasket_get_hw_status(struct gasket_dev *gasket_dev)
{
	int status;
	int i;
	const struct gasket_driver_desc *driver_desc =
		gasket_dev->internal_desc->driver_desc;

	status = gasket_check_and_invoke_callback_nolock(gasket_dev,
							 driver_desc->device_status_cb);
	if (status != GASKET_STATUS_ALIVE) {
		dev_dbg(gasket_dev->dev, "Hardware reported status %d.\n",
			status);
		return status;
	}

	status = gasket_interrupt_system_status(gasket_dev);
	if (status != GASKET_STATUS_ALIVE) {
		dev_dbg(gasket_dev->dev,
			"Interrupt system reported status %d.\n", status);
		return status;
	}

	for (i = 0; i < driver_desc->num_page_tables; ++i) {
		status = gasket_page_table_system_status(gasket_dev->page_table[i]);
		if (status != GASKET_STATUS_ALIVE) {
			dev_dbg(gasket_dev->dev,
				"Page table %d reported status %d.\n",
				i, status);
			return status;
		}
	}

	return GASKET_STATUS_ALIVE;
}
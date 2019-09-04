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
struct toshiba_bluetooth_dev {TYPE_1__* acpi_dev; int /*<<< orphan*/  killswitch; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int toshiba_bluetooth_disable (int /*<<< orphan*/ ) ; 
 int toshiba_bluetooth_enable (int /*<<< orphan*/ ) ; 
 int toshiba_bluetooth_sync_status (struct toshiba_bluetooth_dev*) ; 

__attribute__((used)) static int bt_rfkill_set_block(void *data, bool blocked)
{
	struct toshiba_bluetooth_dev *bt_dev = data;
	int ret;

	ret = toshiba_bluetooth_sync_status(bt_dev);
	if (ret)
		return ret;

	if (!bt_dev->killswitch)
		return 0;

	if (blocked)
		ret = toshiba_bluetooth_disable(bt_dev->acpi_dev->handle);
	else
		ret = toshiba_bluetooth_enable(bt_dev->acpi_dev->handle);

	return ret;
}
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
struct hid_device {struct gb_hid* driver_data; } ;
struct gb_hid {TYPE_2__* connection; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__* bundle; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_HID_STARTED ; 
 int /*<<< orphan*/  GB_HID_TYPE_PWR_OFF ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_hid_set_power (struct gb_hid*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gb_hid_close(struct hid_device *hid)
{
	struct gb_hid *ghid = hid->driver_data;
	int ret;

	clear_bit(GB_HID_STARTED, &ghid->flags);

	/* Save some power */
	ret = gb_hid_set_power(ghid, GB_HID_TYPE_PWR_OFF);
	if (ret)
		dev_err(&ghid->connection->bundle->dev,
			"failed to power off (%d)\n", ret);
}
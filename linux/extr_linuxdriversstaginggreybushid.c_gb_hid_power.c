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
struct hid_device {struct gb_hid* driver_data; } ;
struct gb_hid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_HID_TYPE_PWR_OFF ; 
 int /*<<< orphan*/  GB_HID_TYPE_PWR_ON ; 
#define  PM_HINT_FULLON 129 
#define  PM_HINT_NORMAL 128 
 int gb_hid_set_power (struct gb_hid*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_hid_power(struct hid_device *hid, int lvl)
{
	struct gb_hid *ghid = hid->driver_data;

	switch (lvl) {
	case PM_HINT_FULLON:
		return gb_hid_set_power(ghid, GB_HID_TYPE_PWR_ON);
	case PM_HINT_NORMAL:
		return gb_hid_set_power(ghid, GB_HID_TYPE_PWR_OFF);
	}

	return 0;
}
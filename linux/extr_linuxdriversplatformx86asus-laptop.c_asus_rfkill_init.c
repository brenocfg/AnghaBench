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
struct asus_laptop {scalar_t__ wled_type; scalar_t__ bled_type; int /*<<< orphan*/  wimax; int /*<<< orphan*/  handle; int /*<<< orphan*/  wwan; int /*<<< orphan*/  bluetooth; int /*<<< orphan*/  wlan; int /*<<< orphan*/  gps; scalar_t__ is_pega_lucid; } ;

/* Variables and functions */
 int BT_RSTS ; 
 int ENODEV ; 
 int /*<<< orphan*/  METHOD_BLUETOOTH ; 
 int /*<<< orphan*/  METHOD_GPS_OFF ; 
 int /*<<< orphan*/  METHOD_GPS_ON ; 
 int /*<<< orphan*/  METHOD_GPS_STATUS ; 
 int /*<<< orphan*/  METHOD_WIMAX ; 
 int /*<<< orphan*/  METHOD_WLAN ; 
 int /*<<< orphan*/  METHOD_WWAN ; 
 int /*<<< orphan*/  RFKILL_TYPE_BLUETOOTH ; 
 int /*<<< orphan*/  RFKILL_TYPE_GPS ; 
 int /*<<< orphan*/  RFKILL_TYPE_WIMAX ; 
 int /*<<< orphan*/  RFKILL_TYPE_WLAN ; 
 int /*<<< orphan*/  RFKILL_TYPE_WWAN ; 
 scalar_t__ TYPE_RFKILL ; 
 int WL_RSTS ; 
 int WM_RSTS ; 
 int WW_RSTS ; 
 int /*<<< orphan*/  acpi_check_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asus_gps_rfkill_ops ; 
 int /*<<< orphan*/  asus_rfkill_exit (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_rfkill_ops ; 
 int asus_rfkill_setup (struct asus_laptop*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asus_rfkill_init(struct asus_laptop *asus)
{
	int result = 0;

	if (asus->is_pega_lucid)
		return -ENODEV;

	if (!acpi_check_handle(asus->handle, METHOD_GPS_ON, NULL) &&
	    !acpi_check_handle(asus->handle, METHOD_GPS_OFF, NULL) &&
	    !acpi_check_handle(asus->handle, METHOD_GPS_STATUS, NULL))
		result = asus_rfkill_setup(asus, &asus->gps, "asus-gps",
					   -1, RFKILL_TYPE_GPS,
					   &asus_gps_rfkill_ops);
	if (result)
		goto exit;


	if (!acpi_check_handle(asus->handle, METHOD_WLAN, NULL) &&
	    asus->wled_type == TYPE_RFKILL)
		result = asus_rfkill_setup(asus, &asus->wlan, "asus-wlan",
					   WL_RSTS, RFKILL_TYPE_WLAN,
					   &asus_rfkill_ops);
	if (result)
		goto exit;

	if (!acpi_check_handle(asus->handle, METHOD_BLUETOOTH, NULL) &&
	    asus->bled_type == TYPE_RFKILL)
		result = asus_rfkill_setup(asus, &asus->bluetooth,
					   "asus-bluetooth", BT_RSTS,
					   RFKILL_TYPE_BLUETOOTH,
					   &asus_rfkill_ops);
	if (result)
		goto exit;

	if (!acpi_check_handle(asus->handle, METHOD_WWAN, NULL))
		result = asus_rfkill_setup(asus, &asus->wwan, "asus-wwan",
					   WW_RSTS, RFKILL_TYPE_WWAN,
					   &asus_rfkill_ops);
	if (result)
		goto exit;

	if (!acpi_check_handle(asus->handle, METHOD_WIMAX, NULL))
		result = asus_rfkill_setup(asus, &asus->wimax, "asus-wimax",
					   WM_RSTS, RFKILL_TYPE_WIMAX,
					   &asus_rfkill_ops);
	if (result)
		goto exit;

exit:
	if (result)
		asus_rfkill_exit(asus);

	return result;
}
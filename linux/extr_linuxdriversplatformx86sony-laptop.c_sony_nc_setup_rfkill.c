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
struct rfkill {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;
typedef  enum sony_nc_rfkill { ____Placeholder_sony_nc_rfkill } sony_nc_rfkill ;
typedef  enum rfkill_type { ____Placeholder_rfkill_type } rfkill_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int RFKILL_TYPE_BLUETOOTH ; 
 int RFKILL_TYPE_WIMAX ; 
 int RFKILL_TYPE_WLAN ; 
 int RFKILL_TYPE_WWAN ; 
#define  SONY_BLUETOOTH 131 
#define  SONY_WIFI 130 
#define  SONY_WIMAX 129 
#define  SONY_WWAN 128 
 struct rfkill* rfkill_alloc (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_init_sw_state (struct rfkill*,int) ; 
 int rfkill_register (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_set_hw_state (struct rfkill*,int) ; 
 int sony_call_snc_handle (int /*<<< orphan*/ ,int,int*) ; 
 int* sony_rfkill_address ; 
 struct rfkill** sony_rfkill_devices ; 
 int /*<<< orphan*/  sony_rfkill_handle ; 
 int /*<<< orphan*/  sony_rfkill_ops ; 

__attribute__((used)) static int sony_nc_setup_rfkill(struct acpi_device *device,
				enum sony_nc_rfkill nc_type)
{
	int err;
	struct rfkill *rfk;
	enum rfkill_type type;
	const char *name;
	int result;
	bool hwblock, swblock;

	switch (nc_type) {
	case SONY_WIFI:
		type = RFKILL_TYPE_WLAN;
		name = "sony-wifi";
		break;
	case SONY_BLUETOOTH:
		type = RFKILL_TYPE_BLUETOOTH;
		name = "sony-bluetooth";
		break;
	case SONY_WWAN:
		type = RFKILL_TYPE_WWAN;
		name = "sony-wwan";
		break;
	case SONY_WIMAX:
		type = RFKILL_TYPE_WIMAX;
		name = "sony-wimax";
		break;
	default:
		return -EINVAL;
	}

	rfk = rfkill_alloc(name, &device->dev, type,
			   &sony_rfkill_ops, (void *)nc_type);
	if (!rfk)
		return -ENOMEM;

	err = sony_call_snc_handle(sony_rfkill_handle, 0x200, &result);
	if (err < 0) {
		rfkill_destroy(rfk);
		return err;
	}
	hwblock = !(result & 0x1);

	err = sony_call_snc_handle(sony_rfkill_handle,
				   sony_rfkill_address[nc_type],
				   &result);
	if (err < 0) {
		rfkill_destroy(rfk);
		return err;
	}
	swblock = !(result & 0x2);

	rfkill_init_sw_state(rfk, swblock);
	rfkill_set_hw_state(rfk, hwblock);

	err = rfkill_register(rfk);
	if (err) {
		rfkill_destroy(rfk);
		return err;
	}
	sony_rfkill_devices[nc_type] = rfk;
	return err;
}
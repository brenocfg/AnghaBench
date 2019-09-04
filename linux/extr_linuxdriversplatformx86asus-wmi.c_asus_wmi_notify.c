#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int value; } ;
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {scalar_t__ max_brightness; } ;
struct asus_wmi {scalar_t__ kbd_led_wk; int /*<<< orphan*/  inputdev; TYPE_3__* driver; TYPE_4__ kbd_led; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ acpi_status ;
struct TYPE_7__ {TYPE_2__* quirks; int /*<<< orphan*/  (* key_filter ) (TYPE_3__*,int*,unsigned int*,int*) ;} ;
struct TYPE_6__ {scalar_t__ no_display_toggle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ AE_OK ; 
 int ASUS_WMI_BRN_DOWN ; 
 int ASUS_WMI_BRN_UP ; 
 int ASUS_WMI_KEY_IGNORE ; 
 int NOTIFY_BRNDOWN_MAX ; 
 int NOTIFY_BRNDOWN_MIN ; 
 int NOTIFY_BRNUP_MAX ; 
 int NOTIFY_BRNUP_MIN ; 
 int NOTIFY_KBD_BRTDWN ; 
 int NOTIFY_KBD_BRTTOGGLE ; 
 int NOTIFY_KBD_BRTUP ; 
 scalar_t__ acpi_backlight_vendor ; 
 scalar_t__ acpi_video_get_backlight_type () ; 
 int /*<<< orphan*/  asus_wmi_backlight_notify (struct asus_wmi*,int) ; 
 int /*<<< orphan*/  do_kbd_led_set (TYPE_4__*,scalar_t__) ; 
 scalar_t__ is_display_toggle (int) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  sparse_keymap_report_event (int /*<<< orphan*/ ,int,unsigned int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int*,unsigned int*,int*) ; 
 scalar_t__ wmi_get_event_data (int /*<<< orphan*/ ,struct acpi_buffer*) ; 

__attribute__((used)) static void asus_wmi_notify(u32 value, void *context)
{
	struct asus_wmi *asus = context;
	struct acpi_buffer response = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;
	acpi_status status;
	int code;
	int orig_code;
	unsigned int key_value = 1;
	bool autorelease = 1;

	status = wmi_get_event_data(value, &response);
	if (status != AE_OK) {
		pr_err("bad event status 0x%x\n", status);
		return;
	}

	obj = (union acpi_object *)response.pointer;

	if (!obj || obj->type != ACPI_TYPE_INTEGER)
		goto exit;

	code = obj->integer.value;
	orig_code = code;

	if (asus->driver->key_filter) {
		asus->driver->key_filter(asus->driver, &code, &key_value,
					 &autorelease);
		if (code == ASUS_WMI_KEY_IGNORE)
			goto exit;
	}

	if (code >= NOTIFY_BRNUP_MIN && code <= NOTIFY_BRNUP_MAX)
		code = ASUS_WMI_BRN_UP;
	else if (code >= NOTIFY_BRNDOWN_MIN &&
		 code <= NOTIFY_BRNDOWN_MAX)
		code = ASUS_WMI_BRN_DOWN;

	if (code == ASUS_WMI_BRN_DOWN || code == ASUS_WMI_BRN_UP) {
		if (acpi_video_get_backlight_type() == acpi_backlight_vendor) {
			asus_wmi_backlight_notify(asus, orig_code);
			goto exit;
		}
	}

	if (code == NOTIFY_KBD_BRTUP) {
		do_kbd_led_set(&asus->kbd_led, asus->kbd_led_wk + 1);
		goto exit;
	}
	if (code == NOTIFY_KBD_BRTDWN) {
		do_kbd_led_set(&asus->kbd_led, asus->kbd_led_wk - 1);
		goto exit;
	}
	if (code == NOTIFY_KBD_BRTTOGGLE) {
		if (asus->kbd_led_wk == asus->kbd_led.max_brightness)
			do_kbd_led_set(&asus->kbd_led, 0);
		else
			do_kbd_led_set(&asus->kbd_led, asus->kbd_led_wk + 1);
		goto exit;
	}

	if (is_display_toggle(code) &&
	    asus->driver->quirks->no_display_toggle)
		goto exit;

	if (!sparse_keymap_report_event(asus->inputdev, code,
					key_value, autorelease))
		pr_info("Unknown key %x pressed\n", code);

exit:
	kfree(obj);
}
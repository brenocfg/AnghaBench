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
struct toshiba_acpi_dev {int kbd_type; int kbd_mode; int kbd_time; int /*<<< orphan*/  kbd_event_generated; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int kbd_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int HCI_MISC_SHIFT ; 
 int SCI_KBD_MODE_AUTO ; 
 int SCI_KBD_MODE_FNZ ; 
 int SCI_KBD_MODE_OFF ; 
 int SCI_KBD_MODE_ON ; 
 struct toshiba_acpi_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kbd_bl_work ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 TYPE_1__* toshiba_acpi ; 
 int toshiba_kbd_illum_status_set (struct toshiba_acpi_dev*,int) ; 

__attribute__((used)) static ssize_t kbd_backlight_mode_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	int mode;
	int ret;


	ret = kstrtoint(buf, 0, &mode);
	if (ret)
		return ret;

	/* Check for supported modes depending on keyboard backlight type */
	if (toshiba->kbd_type == 1) {
		/* Type 1 supports SCI_KBD_MODE_FNZ and SCI_KBD_MODE_AUTO */
		if (mode != SCI_KBD_MODE_FNZ && mode != SCI_KBD_MODE_AUTO)
			return -EINVAL;
	} else if (toshiba->kbd_type == 2) {
		/* Type 2 doesn't support SCI_KBD_MODE_FNZ */
		if (mode != SCI_KBD_MODE_AUTO && mode != SCI_KBD_MODE_ON &&
		    mode != SCI_KBD_MODE_OFF)
			return -EINVAL;
	}

	/*
	 * Set the Keyboard Backlight Mode where:
	 *	Auto - KBD backlight turns off automatically in given time
	 *	FN-Z - KBD backlight "toggles" when hotkey pressed
	 *	ON   - KBD backlight is always on
	 *	OFF  - KBD backlight is always off
	 */

	/* Only make a change if the actual mode has changed */
	if (toshiba->kbd_mode != mode) {
		/* Shift the time to "base time" (0x3c0000 == 60 seconds) */
		int time = toshiba->kbd_time << HCI_MISC_SHIFT;

		/* OR the "base time" to the actual method format */
		if (toshiba->kbd_type == 1) {
			/* Type 1 requires the current mode */
			time |= toshiba->kbd_mode;
		} else if (toshiba->kbd_type == 2) {
			/* Type 2 requires the desired mode */
			time |= mode;
		}

		ret = toshiba_kbd_illum_status_set(toshiba, time);
		if (ret)
			return ret;

		toshiba->kbd_mode = mode;
		toshiba_acpi->kbd_mode = mode;

		/*
		 * Some laptop models with the second generation backlit
		 * keyboard (type 2) do not generate the keyboard backlight
		 * changed event (0x92), and thus, the driver will never update
		 * the sysfs entries.
		 *
		 * The event is generated right when changing the keyboard
		 * backlight mode and the *notify function will set the
		 * kbd_event_generated to true.
		 *
		 * In case the event is not generated, schedule the keyboard
		 * backlight work to update the sysfs entries and emulate the
		 * event via genetlink.
		 */
		if (toshiba->kbd_type == 2 &&
		    !toshiba->kbd_event_generated)
			schedule_work(&kbd_bl_work);
	}

	return count;
}
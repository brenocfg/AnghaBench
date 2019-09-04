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
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ rfkill; } ;
struct asus_wmi {TYPE_1__ wlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_WLAN ; 
 int asus_wmi_get_devstate_simple (struct asus_wmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asus_wmi_set_devstate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct asus_wmi* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int asus_hotk_thaw(struct device *device)
{
	struct asus_wmi *asus = dev_get_drvdata(device);

	if (asus->wlan.rfkill) {
		bool wlan;

		/*
		 * Work around bios bug - acpi _PTS turns off the wireless led
		 * during suspend.  Normally it restores it on resume, but
		 * we should kick it ourselves in case hibernation is aborted.
		 */
		wlan = asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_WLAN);
		asus_wmi_set_devstate(ASUS_WMI_DEVID_WLAN, wlan, NULL);
	}

	return 0;
}
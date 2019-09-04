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
typedef  int u8 ;
struct hotplug_slot {struct asus_wmi* private; } ;
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_WLAN ; 
 int asus_wmi_get_devstate_simple (struct asus_wmi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_get_adapter_status(struct hotplug_slot *hotplug_slot,
				   u8 *value)
{
	struct asus_wmi *asus = hotplug_slot->private;
	int result = asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_WLAN);

	if (result < 0)
		return result;

	*value = !!result;
	return 0;
}
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
typedef  int u32 ;
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_WIRELESS_LED ; 
 int ASUS_WMI_DSTS_UNKNOWN_BIT ; 
 int /*<<< orphan*/  asus_wmi_get_devstate (struct asus_wmi*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int wlan_led_unknown_state(struct asus_wmi *asus)
{
	u32 result;

	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_WIRELESS_LED, &result);

	return result & ASUS_WMI_DSTS_UNKNOWN_BIT;
}
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
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_TOUCHPAD_LED ; 
 int asus_wmi_get_devstate_simple (struct asus_wmi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_tpd_led_state(struct asus_wmi *asus)
{
	return asus_wmi_get_devstate_simple(asus, ASUS_WMI_DEVID_TOUCHPAD_LED);
}
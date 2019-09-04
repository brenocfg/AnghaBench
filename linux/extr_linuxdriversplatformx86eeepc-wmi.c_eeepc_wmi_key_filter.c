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
struct asus_wmi_driver {int dummy; } ;

/* Variables and functions */
 int ASUS_WMI_KEY_IGNORE ; 
#define  HOME_HOLD 130 
#define  HOME_PRESS 129 
#define  HOME_RELEASE 128 

__attribute__((used)) static void eeepc_wmi_key_filter(struct asus_wmi_driver *asus_wmi, int *code,
				 unsigned int *value, bool *autorelease)
{
	switch (*code) {
	case HOME_PRESS:
		*value = 1;
		*autorelease = 0;
		break;
	case HOME_HOLD:
		*code = ASUS_WMI_KEY_IGNORE;
		break;
	case HOME_RELEASE:
		*code = HOME_PRESS;
		*value = 0;
		*autorelease = 0;
		break;
	}
}
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
struct samsung_rfkill {scalar_t__ type; struct samsung_laptop* samsung; } ;
struct samsung_laptop {int dummy; } ;
struct sabi_data {int* data; } ;
struct rfkill {int dummy; } ;

/* Variables and functions */
 scalar_t__ RFKILL_TYPE_BLUETOOTH ; 
 scalar_t__ RFKILL_TYPE_WLAN ; 
 size_t WL_STATUS_BT ; 
 size_t WL_STATUS_WLAN ; 
 int /*<<< orphan*/  rfkill_set_sw_state (struct rfkill*,int) ; 
 int swsmi_wireless_status (struct samsung_laptop*,struct sabi_data*) ; 

__attribute__((used)) static void swsmi_rfkill_query(struct rfkill *rfkill, void *priv)
{
	struct samsung_rfkill *srfkill = priv;
	struct samsung_laptop *samsung = srfkill->samsung;
	struct sabi_data data;
	int ret;

	ret = swsmi_wireless_status(samsung, &data);
	if (ret)
		return ;

	if (srfkill->type == RFKILL_TYPE_WLAN)
		ret = data.data[WL_STATUS_WLAN];
	else if (srfkill->type == RFKILL_TYPE_BLUETOOTH)
		ret = data.data[WL_STATUS_BT];
	else
		return ;

	rfkill_set_sw_state(rfkill, !ret);
}
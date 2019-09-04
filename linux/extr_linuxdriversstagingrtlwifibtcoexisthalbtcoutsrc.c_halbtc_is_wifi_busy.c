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
struct TYPE_2__ {scalar_t__ busytraffic; } ;
struct rtl_priv {TYPE_1__ link_info; } ;

/* Variables and functions */

__attribute__((used)) static bool halbtc_is_wifi_busy(struct rtl_priv *rtlpriv)
{
	if (rtlpriv->link_info.busytraffic)
		return true;
	else
		return false;
}
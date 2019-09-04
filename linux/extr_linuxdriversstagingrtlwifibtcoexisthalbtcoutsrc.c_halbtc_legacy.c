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
struct rtl_priv {int dummy; } ;
struct rtl_mac {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ WIRELESS_MODE_B ; 
 scalar_t__ WIRELESS_MODE_G ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 

__attribute__((used)) static bool halbtc_legacy(struct rtl_priv *adapter)
{
	struct rtl_priv *rtlpriv = adapter;
	struct rtl_mac *mac = rtl_mac(rtlpriv);

	bool is_legacy = false;

	if ((mac->mode == WIRELESS_MODE_B) || (mac->mode == WIRELESS_MODE_G))
		is_legacy = true;

	return is_legacy;
}
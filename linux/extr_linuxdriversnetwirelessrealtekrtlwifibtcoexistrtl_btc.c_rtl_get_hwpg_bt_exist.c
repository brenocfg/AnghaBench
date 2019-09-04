#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  btcoexist; } ;
struct TYPE_4__ {TYPE_1__ btc_info; } ;
struct rtl_priv {TYPE_2__ btcoexist; } ;

/* Variables and functions */

u8 rtl_get_hwpg_bt_exist(struct rtl_priv *rtlpriv)
{
	return rtlpriv->btcoexist.btc_info.btcoexist;
}
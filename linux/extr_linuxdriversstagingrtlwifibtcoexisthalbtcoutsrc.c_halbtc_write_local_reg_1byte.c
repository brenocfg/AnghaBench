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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {scalar_t__ chip_interface; struct rtl_priv* adapter; } ;

/* Variables and functions */
 scalar_t__ BTC_INTF_PCI ; 
 scalar_t__ BTC_INTF_SDIO ; 
 scalar_t__ BTC_INTF_USB ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halbtc_write_local_reg_1byte(void *btc_context, u32 reg_addr,
					 u8 data)
{
	struct btc_coexist *btcoexist = (struct btc_coexist *)btc_context;
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	if (btcoexist->chip_interface == BTC_INTF_SDIO)
		;
	else if (btcoexist->chip_interface == BTC_INTF_PCI)
		rtl_write_byte(rtlpriv, reg_addr, data);
	else if (btcoexist->chip_interface == BTC_INTF_USB)
		rtl_write_byte(rtlpriv, reg_addr, data);
}
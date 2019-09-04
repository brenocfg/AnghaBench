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
struct rtl_phy {scalar_t__ current_channel; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static u8 halbtc_get_wifi_central_chnl(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct rtl_phy	*rtlphy = &(rtlpriv->phy);
	u8 chnl = 1;

	if (rtlphy->current_channel != 0)
		chnl = rtlphy->current_channel;
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "static halbtc_get_wifi_central_chnl:%d\n", chnl);
	return chnl;
}
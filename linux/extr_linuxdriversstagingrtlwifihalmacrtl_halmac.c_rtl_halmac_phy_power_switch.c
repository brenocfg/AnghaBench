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
struct rtl_priv {int dummy; } ;
struct halmac_api {int (* halmac_set_hw_value ) (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 struct halmac_api* HALMAC_GET_API (struct halmac_adapter*) ; 
 int /*<<< orphan*/  HALMAC_HW_EN_BB_RF ; 
 int HALMAC_RET_SUCCESS ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 
 int stub1 (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rtl_halmac_phy_power_switch(struct rtl_priv *rtlpriv, u8 enable)
{
	struct halmac_adapter *halmac;
	struct halmac_api *api;
	enum halmac_ret_status status;

	halmac = rtlpriv_to_halmac(rtlpriv);
	if (!halmac)
		return -1;
	api = HALMAC_GET_API(halmac);

	status = api->halmac_set_hw_value(halmac, HALMAC_HW_EN_BB_RF, &enable);
	if (status != HALMAC_RET_SUCCESS)
		return -1;

	return 0;
}
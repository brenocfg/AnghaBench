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
struct halmac_api {int (* halmac_cfg_drv_info ) (struct halmac_adapter*,int) ;} ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_drv_info { ____Placeholder_halmac_drv_info } halmac_drv_info ;

/* Variables and functions */
 struct halmac_api* HALMAC_GET_API (struct halmac_adapter*) ; 
 int HALMAC_RET_SUCCESS ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 
 int stub1 (struct halmac_adapter*,int) ; 

int rtl_halmac_config_rx_info(struct rtl_priv *rtlpriv,
			      enum halmac_drv_info info)
{
	struct halmac_adapter *halmac;
	struct halmac_api *api;
	enum halmac_ret_status status;
	int err = -1;

	halmac = rtlpriv_to_halmac(rtlpriv);
	api = HALMAC_GET_API(halmac);

	status = api->halmac_cfg_drv_info(halmac, info);
	if (status != HALMAC_RET_SUCCESS)
		goto out;

	err = 0;
out:
	return err;
}
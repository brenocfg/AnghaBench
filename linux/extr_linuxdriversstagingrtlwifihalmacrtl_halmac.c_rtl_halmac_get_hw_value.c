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
struct halmac_api {int (* halmac_get_hw_value ) (struct halmac_adapter*,int,void*) ;} ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_hw_id { ____Placeholder_halmac_hw_id } halmac_hw_id ;

/* Variables and functions */
 struct halmac_api* HALMAC_GET_API (struct halmac_adapter*) ; 
 int HALMAC_RET_SUCCESS ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 
 int stub1 (struct halmac_adapter*,int,void*) ; 

int rtl_halmac_get_hw_value(struct rtl_priv *rtlpriv, enum halmac_hw_id hw_id,
			    void *pvalue)
{
	struct halmac_adapter *mac;
	struct halmac_api *api;
	enum halmac_ret_status status;

	mac = rtlpriv_to_halmac(rtlpriv);
	api = HALMAC_GET_API(mac);

	status = api->halmac_get_hw_value(mac, hw_id, pvalue);
	if (status != HALMAC_RET_SUCCESS)
		return -1;

	return 0;
}
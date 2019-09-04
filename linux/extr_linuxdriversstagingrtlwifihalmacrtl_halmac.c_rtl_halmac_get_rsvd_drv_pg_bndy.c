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
typedef  int /*<<< orphan*/  u16 ;
struct rtl_priv {int dummy; } ;
struct halmac_api {int (* halmac_get_hw_value ) (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 struct halmac_api* HALMAC_GET_API (struct halmac_adapter*) ; 
 int /*<<< orphan*/  HALMAC_HW_RSVD_PG_BNDY ; 
 int HALMAC_RET_SUCCESS ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 
 int stub1 (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rtl_halmac_get_rsvd_drv_pg_bndy(struct rtl_priv *rtlpriv, u16 *drv_pg)
{
	enum halmac_ret_status status;
	struct halmac_adapter *halmac = rtlpriv_to_halmac(rtlpriv);
	struct halmac_api *api = HALMAC_GET_API(halmac);

	status = api->halmac_get_hw_value(halmac, HALMAC_HW_RSVD_PG_BNDY,
					  drv_pg);
	if (status != HALMAC_RET_SUCCESS)
		return -1;

	return 0;
}
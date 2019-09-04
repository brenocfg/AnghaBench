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
union halmac_wlan_addr {int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int dummy; } ;
struct halmac_api {int (* halmac_cfg_bssid ) (struct halmac_adapter*,int /*<<< orphan*/ ,union halmac_wlan_addr*) ;} ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 struct halmac_api* HALMAC_GET_API (struct halmac_adapter*) ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (union halmac_wlan_addr*,int /*<<< orphan*/ ,int) ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 
 int stub1 (struct halmac_adapter*,int /*<<< orphan*/ ,union halmac_wlan_addr*) ; 

int rtl_halmac_set_bssid(struct rtl_priv *rtlpriv, u8 hwport, u8 *addr)
{
	struct halmac_adapter *halmac;
	struct halmac_api *api;
	u8 port;
	union halmac_wlan_addr hwa;
	enum halmac_ret_status status;
	int err = -1;

	halmac = rtlpriv_to_halmac(rtlpriv);
	api = HALMAC_GET_API(halmac);
	port = hwport;

	memset(&hwa, 0, sizeof(union halmac_wlan_addr));
	memcpy(hwa.address, addr, 6);
	status = api->halmac_cfg_bssid(halmac, port, &hwa);
	if (status != HALMAC_RET_SUCCESS)
		goto out;

	err = 0;
out:
	return err;
}
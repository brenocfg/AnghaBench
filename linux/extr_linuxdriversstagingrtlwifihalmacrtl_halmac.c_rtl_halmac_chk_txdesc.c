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
struct halmac_api {int (* halmac_chk_txdesc ) (struct halmac_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 struct halmac_api* HALMAC_GET_API (struct halmac_adapter*) ; 
 int HALMAC_RET_SUCCESS ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 
 int stub1 (struct halmac_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rtl_halmac_chk_txdesc(struct rtl_priv *rtlpriv, u8 *txdesc, u32 size)
{
	struct halmac_adapter *mac;
	struct halmac_api *api;
	enum halmac_ret_status status;

	mac = rtlpriv_to_halmac(rtlpriv);
	api = HALMAC_GET_API(mac);

	status = api->halmac_chk_txdesc(mac, txdesc, size);

	if (status != HALMAC_RET_SUCCESS)
		return -1;

	return 0;
}
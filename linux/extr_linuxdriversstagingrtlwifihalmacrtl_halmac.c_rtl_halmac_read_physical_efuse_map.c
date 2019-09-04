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
struct halmac_api {int (* halmac_dump_efuse_map ) (struct halmac_adapter*,int /*<<< orphan*/ ) ;} ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_feature_id { ____Placeholder_halmac_feature_id } halmac_feature_id ;

/* Variables and functions */
 int /*<<< orphan*/  HALMAC_EFUSE_R_DRV ; 
 int HALMAC_FEATURE_DUMP_PHYSICAL_EFUSE ; 
 struct halmac_api* HALMAC_GET_API (struct halmac_adapter*) ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  free_halmac_event (struct rtl_priv*,int) ; 
 int init_halmac_event (struct rtl_priv*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 
 int stub1 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int wait_halmac_event (struct rtl_priv*,int) ; 

int rtl_halmac_read_physical_efuse_map(struct rtl_priv *rtlpriv, u8 *map,
				       u32 size)
{
	struct halmac_adapter *mac;
	struct halmac_api *api;
	enum halmac_ret_status status;
	enum halmac_feature_id id;
	int ret;

	mac = rtlpriv_to_halmac(rtlpriv);
	api = HALMAC_GET_API(mac);
	id = HALMAC_FEATURE_DUMP_PHYSICAL_EFUSE;

	ret = init_halmac_event(rtlpriv, id, map, size);
	if (ret)
		return -1;

	status = api->halmac_dump_efuse_map(mac, HALMAC_EFUSE_R_DRV);
	if (status != HALMAC_RET_SUCCESS) {
		free_halmac_event(rtlpriv, id);
		return -1;
	}

	ret = wait_halmac_event(rtlpriv, id);
	if (ret)
		return -1;

	return 0;
}
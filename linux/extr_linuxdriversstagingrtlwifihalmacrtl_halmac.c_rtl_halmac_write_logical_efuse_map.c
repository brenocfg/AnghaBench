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
typedef  void* u32 ;
struct rtl_priv {int dummy; } ;
struct halmac_pg_efuse_info {void* efuse_mask_size; int /*<<< orphan*/ * efuse_mask; void* efuse_map_size; int /*<<< orphan*/ * efuse_map; } ;
struct halmac_api {int (* halmac_pg_efuse_by_map ) (struct halmac_adapter*,struct halmac_pg_efuse_info*,int /*<<< orphan*/ ) ;} ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  HALMAC_EFUSE_R_AUTO ; 
 struct halmac_api* HALMAC_GET_API (struct halmac_adapter*) ; 
 int HALMAC_RET_SUCCESS ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 
 int stub1 (struct halmac_adapter*,struct halmac_pg_efuse_info*,int /*<<< orphan*/ ) ; 

int rtl_halmac_write_logical_efuse_map(struct rtl_priv *rtlpriv, u8 *map,
				       u32 size, u8 *maskmap, u32 masksize)
{
	struct halmac_adapter *mac;
	struct halmac_api *api;
	struct halmac_pg_efuse_info pginfo;
	enum halmac_ret_status status;

	mac = rtlpriv_to_halmac(rtlpriv);
	api = HALMAC_GET_API(mac);

	pginfo.efuse_map = map;
	pginfo.efuse_map_size = size;
	pginfo.efuse_mask = maskmap;
	pginfo.efuse_mask_size = masksize;

	status = api->halmac_pg_efuse_by_map(mac, &pginfo, HALMAC_EFUSE_R_AUTO);
	if (status != HALMAC_RET_SUCCESS)
		return -1;

	return 0;
}
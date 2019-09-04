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
typedef  scalar_t__ u32 ;
struct rtl_priv {int dummy; } ;
struct halmac_api {int (* halmac_dump_fifo ) (struct halmac_adapter*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;scalar_t__ (* halmac_get_fifo_size ) (struct halmac_adapter*,int) ;} ;
struct halmac_adapter {int dummy; } ;
typedef  int s8 ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum hal_fifo_sel { ____Placeholder_hal_fifo_sel } hal_fifo_sel ;

/* Variables and functions */
 struct halmac_api* HALMAC_GET_API (struct halmac_adapter*) ; 
 int HALMAC_RET_SUCCESS ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 
 scalar_t__ stub1 (struct halmac_adapter*,int) ; 
 int stub2 (struct halmac_adapter*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc (scalar_t__) ; 

int rtl_halmac_dump_fifo(struct rtl_priv *rtlpriv,
			 enum hal_fifo_sel halmac_fifo_sel)
{
	struct halmac_adapter *mac;
	struct halmac_api *api;
	enum halmac_ret_status status;
	u8 *pfifo_map = NULL;
	u32 fifo_size = 0;
	s8 ret = 0;

	mac = rtlpriv_to_halmac(rtlpriv);
	api = HALMAC_GET_API(mac);

	fifo_size = api->halmac_get_fifo_size(mac, halmac_fifo_sel);
	if (fifo_size)
		pfifo_map = vmalloc(fifo_size);
	if (!pfifo_map)
		return -1;

	status = api->halmac_dump_fifo(mac, halmac_fifo_sel, 0, fifo_size,
				       pfifo_map);

	if (status != HALMAC_RET_SUCCESS) {
		ret = -1;
		goto _exit;
	}

_exit:
	if (pfifo_map)
		vfree(pfifo_map);
	return ret;
}
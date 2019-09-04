#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct halmac_adapter* data; } ;
struct TYPE_4__ {TYPE_1__ psd_set; } ;
struct halmac_adapter {int /*<<< orphan*/ * hal_adapter_backup; struct halmac_adapter* halmac_api; TYPE_2__ halmac_state; struct halmac_adapter* hal_efuse_map; void* driver_adapter; } ;
typedef  struct halmac_adapter u8 ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_MSG_INIT ; 
 int HALMAC_RET_ADAPTER_INVALID ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  kfree (struct halmac_adapter*) ; 

enum halmac_ret_status
halmac_deinit_adapter(struct halmac_adapter *halmac_adapter)
{
	void *driver_adapter = NULL;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	driver_adapter = halmac_adapter->driver_adapter;

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"[TRACE]halmac_deinit_adapter_88xx ==========>\n");

	kfree(halmac_adapter->hal_efuse_map);
	halmac_adapter->hal_efuse_map = (u8 *)NULL;

	kfree(halmac_adapter->halmac_state.psd_set.data);
	halmac_adapter->halmac_state.psd_set.data = (u8 *)NULL;

	kfree(halmac_adapter->halmac_api);
	halmac_adapter->halmac_api = NULL;

	halmac_adapter->hal_adapter_backup = NULL;
	kfree(halmac_adapter);

	return HALMAC_RET_SUCCESS;
}
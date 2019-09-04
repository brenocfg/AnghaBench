#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  efuse_size; } ;
struct halmac_adapter {int hal_efuse_map_valid; int /*<<< orphan*/  efuse_lock; void* hal_efuse_map; TYPE_1__ hw_config_info; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HALMAC_RET_EFUSE_R_FAIL ; 
 int HALMAC_RET_MALLOC_FAIL ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 scalar_t__ halmac_read_hw_efuse_88xx (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_dump_efuse_drv_88xx(struct halmac_adapter *halmac_adapter)
{
	u8 *efuse_map = NULL;
	u32 efuse_size;
	void *driver_adapter = NULL;

	driver_adapter = halmac_adapter->driver_adapter;

	efuse_size = halmac_adapter->hw_config_info.efuse_size;

	if (!halmac_adapter->hal_efuse_map) {
		halmac_adapter->hal_efuse_map = kzalloc(efuse_size, GFP_KERNEL);
		if (!halmac_adapter->hal_efuse_map)
			return HALMAC_RET_MALLOC_FAIL;
	}

	efuse_map = kzalloc(efuse_size, GFP_KERNEL);
	if (!efuse_map)
		return HALMAC_RET_MALLOC_FAIL;

	if (halmac_read_hw_efuse_88xx(halmac_adapter, 0, efuse_size,
				      efuse_map) != HALMAC_RET_SUCCESS) {
		kfree(efuse_map);
		return HALMAC_RET_EFUSE_R_FAIL;
	}

	spin_lock(&halmac_adapter->efuse_lock);
	memcpy(halmac_adapter->hal_efuse_map, efuse_map, efuse_size);
	halmac_adapter->hal_efuse_map_valid = true;
	spin_unlock(&halmac_adapter->efuse_lock);

	kfree(efuse_map);

	return HALMAC_RET_SUCCESS;
}
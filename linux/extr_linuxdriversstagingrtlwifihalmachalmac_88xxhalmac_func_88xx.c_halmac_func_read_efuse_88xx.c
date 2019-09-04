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
struct halmac_adapter {scalar_t__ hal_efuse_map; scalar_t__ hal_efuse_map_valid; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_EFUSE_R_FAIL ; 
 int HALMAC_RET_NULL_POINTER ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 scalar_t__ halmac_read_hw_efuse_88xx (struct halmac_adapter*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_func_read_efuse_88xx(struct halmac_adapter *halmac_adapter, u32 offset,
			    u32 size, u8 *efuse_map)
{
	void *driver_adapter = NULL;

	driver_adapter = halmac_adapter->driver_adapter;

	if (!efuse_map) {
		pr_err("Malloc for dump efuse map error\n");
		return HALMAC_RET_NULL_POINTER;
	}

	if (halmac_adapter->hal_efuse_map_valid)
		memcpy(efuse_map, halmac_adapter->hal_efuse_map + offset, size);
	else if (halmac_read_hw_efuse_88xx(halmac_adapter, offset, size,
					   efuse_map) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_EFUSE_R_FAIL;

	return HALMAC_RET_SUCCESS;
}
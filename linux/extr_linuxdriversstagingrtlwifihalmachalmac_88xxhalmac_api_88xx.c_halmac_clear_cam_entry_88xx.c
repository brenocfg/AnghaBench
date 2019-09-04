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
typedef  int u32 ;
struct halmac_cam_entry_format {int dummy; } ;
struct halmac_api {int dummy; } ;
struct TYPE_2__ {int cam_entry_num; } ;
struct halmac_adapter {TYPE_1__ hw_config_info; scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HALMAC_MSG_INIT ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,int /*<<< orphan*/ ,int) ; 
 int HALMAC_RET_ADAPTER_INVALID ; 
 int HALMAC_RET_API_INVALID ; 
 int HALMAC_RET_ENTRY_INDEX_ERROR ; 
 int HALMAC_RET_NULL_POINTER ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REG_CAMCMD ; 
 int /*<<< orphan*/  REG_CAMWRITE ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  kfree (struct halmac_cam_entry_format*) ; 
 struct halmac_cam_entry_format* kzalloc (int,int /*<<< orphan*/ ) ; 

enum halmac_ret_status
halmac_clear_cam_entry_88xx(struct halmac_adapter *halmac_adapter,
			    u32 entry_index)
{
	u32 i;
	u32 command = 0x80010000;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;
	struct halmac_cam_entry_format *cam_entry_format;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"[TRACE]halmac_clear_security_cam_88xx ==========>\n");

	if (entry_index >= halmac_adapter->hw_config_info.cam_entry_num)
		return HALMAC_RET_ENTRY_INDEX_ERROR;

	cam_entry_format = kzalloc(sizeof(*cam_entry_format), GFP_KERNEL);
	if (!cam_entry_format)
		return HALMAC_RET_NULL_POINTER;

	for (i = 0; i < 8; i++) {
		HALMAC_REG_WRITE_32(halmac_adapter, REG_CAMWRITE,
				    *((u32 *)cam_entry_format + i));
		HALMAC_REG_WRITE_32(halmac_adapter, REG_CAMCMD,
				    command | ((entry_index << 3) + i));
	}

	kfree(cam_entry_format);

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"[TRACE]halmac_clear_security_cam_88xx <==========\n");

	return HALMAC_RET_SUCCESS;
}
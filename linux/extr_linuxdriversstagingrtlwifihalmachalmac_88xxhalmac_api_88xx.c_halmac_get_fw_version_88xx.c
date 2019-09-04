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
struct halmac_fw_version {int /*<<< orphan*/  sub_index; int /*<<< orphan*/  sub_version; int /*<<< orphan*/  version; } ;
struct TYPE_4__ {int /*<<< orphan*/  sub_index; int /*<<< orphan*/  sub_version; int /*<<< orphan*/  version; } ;
struct TYPE_3__ {scalar_t__ dlfw_state; } ;
struct halmac_adapter {TYPE_2__ fw_version; TYPE_1__ halmac_state; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_ADAPTER_INVALID ; 
 int HALMAC_RET_DLFW_FAIL ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 

enum halmac_ret_status
halmac_get_fw_version_88xx(struct halmac_adapter *halmac_adapter,
			   struct halmac_fw_version *fw_version)
{
	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_adapter->halmac_state.dlfw_state == 0)
		return HALMAC_RET_DLFW_FAIL;

	fw_version->version = halmac_adapter->fw_version.version;
	fw_version->sub_version = halmac_adapter->fw_version.sub_version;
	fw_version->sub_index = halmac_adapter->fw_version.sub_index;

	return HALMAC_RET_SUCCESS;
}
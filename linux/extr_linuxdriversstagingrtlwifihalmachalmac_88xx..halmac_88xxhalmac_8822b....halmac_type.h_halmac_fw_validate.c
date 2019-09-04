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
struct TYPE_2__ {scalar_t__ dlfw_state; } ;
struct halmac_adapter {TYPE_1__ halmac_state; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 scalar_t__ HALMAC_DLFW_DONE ; 
 scalar_t__ HALMAC_GEN_INFO_SENT ; 
 int HALMAC_RET_NO_DLFW ; 
 int HALMAC_RET_SUCCESS ; 

__attribute__((used)) static inline enum halmac_ret_status
halmac_fw_validate(struct halmac_adapter *halmac_adapter)
{
	if (halmac_adapter->halmac_state.dlfw_state != HALMAC_DLFW_DONE &&
	    halmac_adapter->halmac_state.dlfw_state != HALMAC_GEN_INFO_SENT)
		return HALMAC_RET_NO_DLFW;

	return HALMAC_RET_SUCCESS;
}
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
struct halmac_scan_state_set {int process_status; } ;
struct TYPE_2__ {struct halmac_scan_state_set scan_state_set; } ;
struct halmac_adapter {TYPE_1__ halmac_state; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_cmd_process_status { ____Placeholder_halmac_cmd_process_status } halmac_cmd_process_status ;

/* Variables and functions */
 int HALMAC_RET_SUCCESS ; 

enum halmac_ret_status halmac_query_channel_switch_status_88xx(
	struct halmac_adapter *halmac_adapter,
	enum halmac_cmd_process_status *process_status, u8 *data, u32 *size)
{
	struct halmac_scan_state_set *scan_state_set =
		&halmac_adapter->halmac_state.scan_state_set;

	*process_status = scan_state_set->process_status;

	return HALMAC_RET_SUCCESS;
}
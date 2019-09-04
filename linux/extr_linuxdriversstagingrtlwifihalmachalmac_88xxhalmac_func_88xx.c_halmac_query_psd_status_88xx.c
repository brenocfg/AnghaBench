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
typedef  scalar_t__ u32 ;
struct halmac_psd_state_set {int process_status; scalar_t__ data_size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {struct halmac_psd_state_set psd_set; } ;
struct halmac_adapter {void* driver_adapter; TYPE_1__ halmac_state; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_cmd_process_status { ____Placeholder_halmac_cmd_process_status } halmac_cmd_process_status ;

/* Variables and functions */
 int HALMAC_CMD_PROCESS_DONE ; 
 int HALMAC_RET_BUFFER_TOO_SMALL ; 
 int HALMAC_RET_NULL_POINTER ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

enum halmac_ret_status
halmac_query_psd_status_88xx(struct halmac_adapter *halmac_adapter,
			     enum halmac_cmd_process_status *process_status,
			     u8 *data, u32 *size)
{
	void *driver_adapter = NULL;
	struct halmac_psd_state_set *psd_set =
		&halmac_adapter->halmac_state.psd_set;

	driver_adapter = halmac_adapter->driver_adapter;

	*process_status = psd_set->process_status;

	if (!data)
		return HALMAC_RET_NULL_POINTER;

	if (!size)
		return HALMAC_RET_NULL_POINTER;

	if (*process_status == HALMAC_CMD_PROCESS_DONE) {
		if (*size < psd_set->data_size) {
			*size = psd_set->data_size;
			return HALMAC_RET_BUFFER_TOO_SMALL;
		}

		*size = psd_set->data_size;
		memcpy(data, psd_set->data, *size);
	}

	return HALMAC_RET_SUCCESS;
}
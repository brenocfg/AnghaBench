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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct halmac_psd_state_set {scalar_t__ seq_num; scalar_t__ process_status; scalar_t__ segment_size; scalar_t__ data_size; scalar_t__ data; } ;
struct TYPE_2__ {struct halmac_psd_state_set psd_set; } ;
struct halmac_adapter {TYPE_1__ halmac_state; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_cmd_process_status { ____Placeholder_halmac_cmd_process_status } halmac_cmd_process_status ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HALMAC_C2H_DATA_OFFSET_88XX ; 
 int HALMAC_CMD_PROCESS_DONE ; 
 scalar_t__ HALMAC_CMD_PROCESS_SENDING ; 
 int /*<<< orphan*/  HALMAC_FEATURE_PSD ; 
 int /*<<< orphan*/  HALMAC_MSG_H2C ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PLATFORM_EVENT_INDICATION (void*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PSD_DATA_GET_END_SEGMENT (scalar_t__*) ; 
 scalar_t__ PSD_DATA_GET_H2C_SEQ (scalar_t__*) ; 
 scalar_t__ PSD_DATA_GET_SEGMENT_ID (scalar_t__*) ; 
 scalar_t__ PSD_DATA_GET_SEGMENT_SIZE (scalar_t__*) ; 
 scalar_t__ PSD_DATA_GET_TOTAL_SIZE (scalar_t__*) ; 
 scalar_t__ kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_parse_psd_data_88xx(struct halmac_adapter *halmac_adapter, u8 *c2h_buf,
			   u32 c2h_size)
{
	u8 segment_id = 0, segment_size = 0, h2c_seq = 0;
	u16 total_size;
	void *driver_adapter = halmac_adapter->driver_adapter;
	enum halmac_cmd_process_status process_status;
	struct halmac_psd_state_set *psd_set =
		&halmac_adapter->halmac_state.psd_set;

	h2c_seq = (u8)PSD_DATA_GET_H2C_SEQ(c2h_buf);
	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
			"[TRACE]Seq num : h2c -> %d c2h -> %d\n",
			psd_set->seq_num, h2c_seq);
	if (h2c_seq != psd_set->seq_num) {
		pr_err("[ERR]Seq num mismatch : h2c -> %d c2h -> %d\n",
		       psd_set->seq_num, h2c_seq);
		return HALMAC_RET_SUCCESS;
	}

	if (psd_set->process_status != HALMAC_CMD_PROCESS_SENDING) {
		pr_err("[ERR]Not in HALMAC_CMD_PROCESS_SENDING\n");
		return HALMAC_RET_SUCCESS;
	}

	total_size = (u16)PSD_DATA_GET_TOTAL_SIZE(c2h_buf);
	segment_id = (u8)PSD_DATA_GET_SEGMENT_ID(c2h_buf);
	segment_size = (u8)PSD_DATA_GET_SEGMENT_SIZE(c2h_buf);
	psd_set->data_size = total_size;

	if (!psd_set->data)
		psd_set->data = kzalloc(psd_set->data_size, GFP_KERNEL);

	if (segment_id == 0)
		psd_set->segment_size = segment_size;

	memcpy(psd_set->data + segment_id * psd_set->segment_size,
	       c2h_buf + HALMAC_C2H_DATA_OFFSET_88XX, segment_size);

	if (!PSD_DATA_GET_END_SEGMENT(c2h_buf))
		return HALMAC_RET_SUCCESS;

	process_status = HALMAC_CMD_PROCESS_DONE;
	psd_set->process_status = process_status;

	PLATFORM_EVENT_INDICATION(driver_adapter, HALMAC_FEATURE_PSD,
				  process_status, psd_set->data,
				  psd_set->data_size);

	return HALMAC_RET_SUCCESS;
}
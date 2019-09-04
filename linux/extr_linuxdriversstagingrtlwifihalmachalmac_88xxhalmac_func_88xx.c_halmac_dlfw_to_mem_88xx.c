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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct halmac_api {int dummy; } ;
struct TYPE_2__ {scalar_t__ txdesc_size; } ;
struct halmac_adapter {scalar_t__ max_download_size; TYPE_1__ hw_config_info; scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT_DDMACH0_RESET_CHKSUM_STS ; 
 scalar_t__ HALMAC_OCPBASE_TXBUF_88XX ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,int /*<<< orphan*/ ,int) ; 
 int HALMAC_RET_DLFW_FAIL ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  REG_DDMA_CH0CTRL ; 
 scalar_t__ halmac_check_fw_chksum_88xx (struct halmac_adapter*,scalar_t__) ; 
 scalar_t__ halmac_iddma_dlfw_88xx (struct halmac_adapter*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ halmac_send_fwpkt_88xx (struct halmac_adapter*,int*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_dlfw_to_mem_88xx(struct halmac_adapter *halmac_adapter, u8 *ram_code,
			u32 dest, u32 code_size)
{
	u8 *code_ptr;
	u8 first_part;
	u32 mem_offset;
	u32 pkt_size_tmp, send_pkt_size;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	code_ptr = ram_code;
	mem_offset = 0;
	first_part = 1;
	pkt_size_tmp = code_size;

	HALMAC_REG_WRITE_32(
		halmac_adapter, REG_DDMA_CH0CTRL,
		HALMAC_REG_READ_32(halmac_adapter, REG_DDMA_CH0CTRL) |
			BIT_DDMACH0_RESET_CHKSUM_STS);

	while (pkt_size_tmp != 0) {
		if (pkt_size_tmp >= halmac_adapter->max_download_size)
			send_pkt_size = halmac_adapter->max_download_size;
		else
			send_pkt_size = pkt_size_tmp;

		if (halmac_send_fwpkt_88xx(
			    halmac_adapter, code_ptr + mem_offset,
			    send_pkt_size) != HALMAC_RET_SUCCESS) {
			pr_err("halmac_send_fwpkt_88xx fail!!\n");
			return HALMAC_RET_DLFW_FAIL;
		}

		if (halmac_iddma_dlfw_88xx(
			    halmac_adapter,
			    HALMAC_OCPBASE_TXBUF_88XX +
				    halmac_adapter->hw_config_info.txdesc_size,
			    dest + mem_offset, send_pkt_size,
			    first_part) != HALMAC_RET_SUCCESS) {
			pr_err("halmac_iddma_dlfw_88xx fail!!\n");
			return HALMAC_RET_DLFW_FAIL;
		}

		first_part = 0;
		mem_offset += send_pkt_size;
		pkt_size_tmp -= send_pkt_size;
	}

	if (halmac_check_fw_chksum_88xx(halmac_adapter, dest) !=
	    HALMAC_RET_SUCCESS) {
		pr_err("halmac_check_fw_chksum_88xx fail!!\n");
		return HALMAC_RET_DLFW_FAIL;
	}

	return HALMAC_RET_SUCCESS;
}
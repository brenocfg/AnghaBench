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
typedef  int /*<<< orphan*/  u32 ;
struct halmac_adapter {void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ GET_RX_DESC_C2H (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HALMAC_API_GET_C2H_INFO ; 
 int /*<<< orphan*/  HALMAC_MSG_H2C ; 
 int HALMAC_RET_ADAPTER_INVALID ; 
 int HALMAC_RET_API_INVALID ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_api_record_id_88xx (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 
 int halmac_parse_c2h_packet_88xx (struct halmac_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

enum halmac_ret_status
halmac_get_c2h_info_88xx(struct halmac_adapter *halmac_adapter, u8 *halmac_buf,
			 u32 halmac_size)
{
	void *driver_adapter = NULL;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	halmac_api_record_id_88xx(halmac_adapter, HALMAC_API_GET_C2H_INFO);

	driver_adapter = halmac_adapter->driver_adapter;

	/* Check if it is C2H packet */
	if (GET_RX_DESC_C2H(halmac_buf)) {
		HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
				"C2H packet, start parsing!\n");

		status = halmac_parse_c2h_packet_88xx(halmac_adapter,
						      halmac_buf, halmac_size);

		if (status != HALMAC_RET_SUCCESS) {
			pr_err("halmac_parse_c2h_packet_88xx error = %x\n",
			       status);
			return status;
		}
	}

	return HALMAC_RET_SUCCESS;
}
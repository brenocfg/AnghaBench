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
struct halmac_adapter {scalar_t__ h2c_buf_free_space; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ HALMAC_H2C_CMD_SIZE_UNIT_88XX ; 
 int /*<<< orphan*/  HALMAC_MSG_H2C ; 
 int HALMAC_RET_H2C_SPACE_FULL ; 
 int HALMAC_RET_SEND_H2C_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  PLATFORM_SEND_H2C_PKT (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  halmac_get_h2c_buff_free_space_88xx (struct halmac_adapter*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_send_h2c_pkt_88xx(struct halmac_adapter *halmac_adapter, u8 *hal_h2c_cmd,
			 u32 size, bool ack)
{
	u32 counter = 100;
	void *driver_adapter = halmac_adapter->driver_adapter;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	while (halmac_adapter->h2c_buf_free_space <=
	       HALMAC_H2C_CMD_SIZE_UNIT_88XX) {
		halmac_get_h2c_buff_free_space_88xx(halmac_adapter);
		counter--;
		if (counter == 0) {
			pr_err("h2c free space is not enough!!\n");
			return HALMAC_RET_H2C_SPACE_FULL;
		}
	}

	/* Send TxDesc + H2C_CMD */
	if (!PLATFORM_SEND_H2C_PKT(driver_adapter, hal_h2c_cmd, size)) {
		pr_err("Send H2C_CMD pkt error!!\n");
		return HALMAC_RET_SEND_H2C_FAIL;
	}

	halmac_adapter->h2c_buf_free_space -= HALMAC_H2C_CMD_SIZE_UNIT_88XX;

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
			"H2C free space : %d\n",
			halmac_adapter->h2c_buf_free_space);

	return status;
}
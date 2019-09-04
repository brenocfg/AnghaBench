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
typedef  int u32 ;
struct halmac_api {int dummy; } ;
struct TYPE_2__ {scalar_t__ rx_fifo_expanding_mode; int rsvd_h2c_queue_pg_bndy; } ;
struct halmac_adapter {int trx_mode; int h2c_buff_size; int h2c_buf_free_space; TYPE_1__ txff_allocation; scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_trx_mode { ____Placeholder_halmac_trx_mode } halmac_trx_mode ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_API_INIT_TRX_CFG ; 
 int HALMAC_CR_TRX_ENABLE_8822B ; 
 int /*<<< orphan*/  HALMAC_MSG_INIT ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int HALMAC_REG_READ_8 (struct halmac_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int) ; 
 int HALMAC_RET_ADAPTER_INVALID ; 
 int HALMAC_RET_API_INVALID ; 
 int HALMAC_RET_GET_H2C_SPACE_ERR ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int HALMAC_RSVD_H2C_QUEUE_PGNUM_8822B ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ HALMAC_RX_FIFO_EXPANDING_MODE_DISABLE ; 
 int HALMAC_TX_PAGE_SIZE_2_POWER_8822B ; 
 scalar_t__ REG_CR ; 
 int /*<<< orphan*/  REG_H2CQ_CSR ; 
 int /*<<< orphan*/  REG_H2C_HEAD ; 
 scalar_t__ REG_H2C_INFO ; 
 int /*<<< orphan*/  REG_H2C_READ_ADDR ; 
 int /*<<< orphan*/  REG_H2C_TAIL ; 
 scalar_t__ REG_RX_DRVINFO_SZ ; 
 scalar_t__ REG_TXDMA_OFFSET_CHK ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_api_record_id_88xx (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_get_h2c_buff_free_space_88xx (struct halmac_adapter*) ; 
 int halmac_priority_queue_config_8822b (struct halmac_adapter*,int) ; 
 int halmac_txdma_queue_mapping_8822b (struct halmac_adapter*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_init_trx_cfg_8822b(struct halmac_adapter *halmac_adapter,
			  enum halmac_trx_mode halmac_trx_mode)
{
	u8 value8;
	u32 value32;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	halmac_api_record_id_88xx(halmac_adapter, HALMAC_API_INIT_TRX_CFG);

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;
	halmac_adapter->trx_mode = halmac_trx_mode;

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"halmac_init_trx_cfg ==========>halmac_trx_mode = %d\n",
			halmac_trx_mode);

	status = halmac_txdma_queue_mapping_8822b(halmac_adapter,
						  halmac_trx_mode);

	if (status != HALMAC_RET_SUCCESS) {
		HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
				"halmac_txdma_queue_mapping fail!\n");
		return status;
	}

	value8 = 0;
	HALMAC_REG_WRITE_8(halmac_adapter, REG_CR, value8);
	value8 = HALMAC_CR_TRX_ENABLE_8822B;
	HALMAC_REG_WRITE_8(halmac_adapter, REG_CR, value8);
	HALMAC_REG_WRITE_32(halmac_adapter, REG_H2CQ_CSR, BIT(31));

	status = halmac_priority_queue_config_8822b(halmac_adapter,
						    halmac_trx_mode);
	if (halmac_adapter->txff_allocation.rx_fifo_expanding_mode !=
	    HALMAC_RX_FIFO_EXPANDING_MODE_DISABLE)
		HALMAC_REG_WRITE_8(halmac_adapter, REG_RX_DRVINFO_SZ, 0xF);

	if (status != HALMAC_RET_SUCCESS) {
		HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
				"halmac_txdma_queue_mapping fail!\n");
		return status;
	}

	/* Config H2C packet buffer */
	value32 = HALMAC_REG_READ_32(halmac_adapter, REG_H2C_HEAD);
	value32 = (value32 & 0xFFFC0000) |
		  (halmac_adapter->txff_allocation.rsvd_h2c_queue_pg_bndy
		   << HALMAC_TX_PAGE_SIZE_2_POWER_8822B);
	HALMAC_REG_WRITE_32(halmac_adapter, REG_H2C_HEAD, value32);

	value32 = HALMAC_REG_READ_32(halmac_adapter, REG_H2C_READ_ADDR);
	value32 = (value32 & 0xFFFC0000) |
		  (halmac_adapter->txff_allocation.rsvd_h2c_queue_pg_bndy
		   << HALMAC_TX_PAGE_SIZE_2_POWER_8822B);
	HALMAC_REG_WRITE_32(halmac_adapter, REG_H2C_READ_ADDR, value32);

	value32 = HALMAC_REG_READ_32(halmac_adapter, REG_H2C_TAIL);
	value32 = (value32 & 0xFFFC0000) |
		  ((halmac_adapter->txff_allocation.rsvd_h2c_queue_pg_bndy
		    << HALMAC_TX_PAGE_SIZE_2_POWER_8822B) +
		   (HALMAC_RSVD_H2C_QUEUE_PGNUM_8822B
		    << HALMAC_TX_PAGE_SIZE_2_POWER_8822B));
	HALMAC_REG_WRITE_32(halmac_adapter, REG_H2C_TAIL, value32);

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_H2C_INFO);
	value8 = (u8)((value8 & 0xFC) | 0x01);
	HALMAC_REG_WRITE_8(halmac_adapter, REG_H2C_INFO, value8);

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_H2C_INFO);
	value8 = (u8)((value8 & 0xFB) | 0x04);
	HALMAC_REG_WRITE_8(halmac_adapter, REG_H2C_INFO, value8);

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_TXDMA_OFFSET_CHK + 1);
	value8 = (u8)((value8 & 0x7f) | 0x80);
	HALMAC_REG_WRITE_8(halmac_adapter, REG_TXDMA_OFFSET_CHK + 1, value8);

	halmac_adapter->h2c_buff_size = HALMAC_RSVD_H2C_QUEUE_PGNUM_8822B
					<< HALMAC_TX_PAGE_SIZE_2_POWER_8822B;
	halmac_get_h2c_buff_free_space_88xx(halmac_adapter);

	if (halmac_adapter->h2c_buff_size !=
	    halmac_adapter->h2c_buf_free_space) {
		pr_err("get h2c free space error!\n");
		return HALMAC_RET_GET_H2C_SPACE_ERR;
	}

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT, DBG_DMESG,
			"halmac_init_trx_cfg <==========\n");

	return HALMAC_RET_SUCCESS;
}
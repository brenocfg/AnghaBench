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
typedef  int /*<<< orphan*/  u16 ;
struct halmac_rqpn_ {int dummy; } ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_interface; int halmac_bulkout_num; int /*<<< orphan*/ * halmac_ptcl_queue; scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_trx_mode { ____Placeholder_halmac_trx_mode } halmac_trx_mode ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_TXDMA_BEQ_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_TXDMA_BKQ_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_TXDMA_HIQ_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_TXDMA_MGQ_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_TXDMA_VIQ_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_TXDMA_VOQ_MAP (int /*<<< orphan*/ ) ; 
 scalar_t__ HALMAC_INTERFACE_PCIE ; 
 scalar_t__ HALMAC_INTERFACE_SDIO ; 
 scalar_t__ HALMAC_INTERFACE_USB ; 
 size_t HALMAC_PTCL_QUEUE_BE ; 
 size_t HALMAC_PTCL_QUEUE_BK ; 
 size_t HALMAC_PTCL_QUEUE_HI ; 
 size_t HALMAC_PTCL_QUEUE_MG ; 
 size_t HALMAC_PTCL_QUEUE_VI ; 
 size_t HALMAC_PTCL_QUEUE_VO ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_16 (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HALMAC_RET_NOT_SUPPORT ; 
 int HALMAC_RET_SUCCESS ; 
 struct halmac_rqpn_* HALMAC_RQPN_2BULKOUT_8822B ; 
 struct halmac_rqpn_* HALMAC_RQPN_3BULKOUT_8822B ; 
 struct halmac_rqpn_* HALMAC_RQPN_4BULKOUT_8822B ; 
 struct halmac_rqpn_* HALMAC_RQPN_PCIE_8822B ; 
 struct halmac_rqpn_* HALMAC_RQPN_SDIO_8822B ; 
 int /*<<< orphan*/  REG_TXDMA_PQ_MAP ; 
 int halmac_rqpn_parser_88xx (struct halmac_adapter*,int,struct halmac_rqpn_*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_txdma_queue_mapping_8822b(struct halmac_adapter *halmac_adapter,
				 enum halmac_trx_mode halmac_trx_mode)
{
	u16 value16;
	void *driver_adapter = NULL;
	struct halmac_rqpn_ *curr_rqpn_sel = NULL;
	enum halmac_ret_status status;
	struct halmac_api *halmac_api;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	if (halmac_adapter->halmac_interface == HALMAC_INTERFACE_SDIO) {
		curr_rqpn_sel = HALMAC_RQPN_SDIO_8822B;
	} else if (halmac_adapter->halmac_interface == HALMAC_INTERFACE_PCIE) {
		curr_rqpn_sel = HALMAC_RQPN_PCIE_8822B;
	} else if (halmac_adapter->halmac_interface == HALMAC_INTERFACE_USB) {
		if (halmac_adapter->halmac_bulkout_num == 2) {
			curr_rqpn_sel = HALMAC_RQPN_2BULKOUT_8822B;
		} else if (halmac_adapter->halmac_bulkout_num == 3) {
			curr_rqpn_sel = HALMAC_RQPN_3BULKOUT_8822B;
		} else if (halmac_adapter->halmac_bulkout_num == 4) {
			curr_rqpn_sel = HALMAC_RQPN_4BULKOUT_8822B;
		} else {
			pr_err("[ERR]interface not support\n");
			return HALMAC_RET_NOT_SUPPORT;
		}
	} else {
		return HALMAC_RET_NOT_SUPPORT;
	}

	status = halmac_rqpn_parser_88xx(halmac_adapter, halmac_trx_mode,
					 curr_rqpn_sel);
	if (status != HALMAC_RET_SUCCESS)
		return status;

	value16 = 0;
	value16 |= BIT_TXDMA_HIQ_MAP(
		halmac_adapter->halmac_ptcl_queue[HALMAC_PTCL_QUEUE_HI]);
	value16 |= BIT_TXDMA_MGQ_MAP(
		halmac_adapter->halmac_ptcl_queue[HALMAC_PTCL_QUEUE_MG]);
	value16 |= BIT_TXDMA_BKQ_MAP(
		halmac_adapter->halmac_ptcl_queue[HALMAC_PTCL_QUEUE_BK]);
	value16 |= BIT_TXDMA_BEQ_MAP(
		halmac_adapter->halmac_ptcl_queue[HALMAC_PTCL_QUEUE_BE]);
	value16 |= BIT_TXDMA_VIQ_MAP(
		halmac_adapter->halmac_ptcl_queue[HALMAC_PTCL_QUEUE_VI]);
	value16 |= BIT_TXDMA_VOQ_MAP(
		halmac_adapter->halmac_ptcl_queue[HALMAC_PTCL_QUEUE_VO]);
	HALMAC_REG_WRITE_16(halmac_adapter, REG_TXDMA_PQ_MAP, value16);

	return HALMAC_RET_SUCCESS;
}
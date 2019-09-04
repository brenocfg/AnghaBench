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
typedef  int u32 ;
struct TYPE_3__ {int rsvd_pg_bndy; } ;
struct TYPE_4__ {int tx_fifo_size; int rx_fifo_size; } ;
struct halmac_adapter {TYPE_1__ txff_allocation; TYPE_2__ hw_config_info; } ;
typedef  enum hal_fifo_sel { ____Placeholder_hal_fifo_sel } hal_fifo_sel ;

/* Variables and functions */
 int /*<<< orphan*/  HALMAC_API_GET_FIFO_SIZE ; 
 int HALMAC_RET_ADAPTER_INVALID ; 
 int HALMAC_RET_API_INVALID ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int HAL_FIFO_SEL_LLT ; 
 int HAL_FIFO_SEL_REPORT ; 
 int HAL_FIFO_SEL_RSVD_PAGE ; 
 int HAL_FIFO_SEL_RX ; 
 int HAL_FIFO_SEL_TX ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_api_record_id_88xx (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 

u32 halmac_get_fifo_size_88xx(struct halmac_adapter *halmac_adapter,
			      enum hal_fifo_sel halmac_fifo_sel)
{
	u32 fifo_size = 0;

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	halmac_api_record_id_88xx(halmac_adapter, HALMAC_API_GET_FIFO_SIZE);

	if (halmac_fifo_sel == HAL_FIFO_SEL_TX)
		fifo_size = halmac_adapter->hw_config_info.tx_fifo_size;
	else if (halmac_fifo_sel == HAL_FIFO_SEL_RX)
		fifo_size = halmac_adapter->hw_config_info.rx_fifo_size;
	else if (halmac_fifo_sel == HAL_FIFO_SEL_RSVD_PAGE)
		fifo_size =
			((halmac_adapter->hw_config_info.tx_fifo_size >> 7) -
			 halmac_adapter->txff_allocation.rsvd_pg_bndy)
			<< 7;
	else if (halmac_fifo_sel == HAL_FIFO_SEL_REPORT)
		fifo_size = 65536;
	else if (halmac_fifo_sel == HAL_FIFO_SEL_LLT)
		fifo_size = 65536;

	return fifo_size;
}
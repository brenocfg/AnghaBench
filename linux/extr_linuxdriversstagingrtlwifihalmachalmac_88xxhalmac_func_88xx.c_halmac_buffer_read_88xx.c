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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct halmac_api {int dummy; } ;
struct TYPE_2__ {int rsvd_pg_bndy; } ;
struct halmac_adapter {TYPE_1__ txff_allocation; scalar_t__ halmac_api; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum hal_fifo_sel { ____Placeholder_hal_fifo_sel } hal_fifo_sel ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int HALMAC_REG_READ_16 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_16 (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HALMAC_RET_NOT_SUPPORT ; 
 int HALMAC_RET_SUCCESS ; 
 int HAL_FIFO_SEL_LLT ; 
 int HAL_FIFO_SEL_REPORT ; 
 int HAL_FIFO_SEL_RSVD_PAGE ; 
 int HAL_FIFO_SEL_RX ; 
 int HAL_FIFO_SEL_TX ; 
 int /*<<< orphan*/  REG_PKTBUF_DBG_CTRL ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

enum halmac_ret_status
halmac_buffer_read_88xx(struct halmac_adapter *halmac_adapter, u32 offset,
			u32 size, enum hal_fifo_sel halmac_fifo_sel,
			u8 *fifo_map)
{
	u32 start_page, value_read;
	u32 i, counter = 0, residue;
	struct halmac_api *halmac_api;

	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	if (halmac_fifo_sel == HAL_FIFO_SEL_RSVD_PAGE)
		offset = offset +
			 (halmac_adapter->txff_allocation.rsvd_pg_bndy << 7);

	start_page = offset >> 12;
	residue = offset & (4096 - 1);

	if (halmac_fifo_sel == HAL_FIFO_SEL_TX ||
	    halmac_fifo_sel == HAL_FIFO_SEL_RSVD_PAGE)
		start_page += 0x780;
	else if (halmac_fifo_sel == HAL_FIFO_SEL_RX)
		start_page += 0x700;
	else if (halmac_fifo_sel == HAL_FIFO_SEL_REPORT)
		start_page += 0x660;
	else if (halmac_fifo_sel == HAL_FIFO_SEL_LLT)
		start_page += 0x650;
	else
		return HALMAC_RET_NOT_SUPPORT;

	value_read = HALMAC_REG_READ_16(halmac_adapter, REG_PKTBUF_DBG_CTRL);

	do {
		HALMAC_REG_WRITE_16(halmac_adapter, REG_PKTBUF_DBG_CTRL,
				    (u16)(start_page | (value_read & 0xF000)));

		for (i = 0x8000 + residue; i <= 0x8FFF; i += 4) {
			*(u32 *)(fifo_map + counter) =
				HALMAC_REG_READ_32(halmac_adapter, i);
			*(u32 *)(fifo_map + counter) =
				le32_to_cpu(*(__le32 *)(fifo_map + counter));
			counter += 4;
			if (size == counter)
				goto HALMAC_BUF_READ_OK;
		}

		residue = 0;
		start_page++;
	} while (1);

HALMAC_BUF_READ_OK:
	HALMAC_REG_WRITE_16(halmac_adapter, REG_PKTBUF_DBG_CTRL,
			    (u16)value_read);

	return HALMAC_RET_SUCCESS;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__** data_fifo; } ;
typedef  TYPE_1__ dwc_otg_core_if_t ;
struct TYPE_6__ {scalar_t__ xfer_buff; size_t hc_num; scalar_t__ xfer_len; scalar_t__ xfer_count; scalar_t__ max_packet; } ;
typedef  TYPE_2__ dwc_hc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WRITE_REG32 (scalar_t__*,scalar_t__) ; 

void dwc_otg_hc_write_packet(dwc_otg_core_if_t * core_if, dwc_hc_t * hc)
{
	uint32_t i;
	uint32_t remaining_count;
	uint32_t byte_count;
	uint32_t dword_count;

	uint32_t *data_buff = (uint32_t *) (hc->xfer_buff);
	uint32_t *data_fifo = core_if->data_fifo[hc->hc_num];

	remaining_count = hc->xfer_len - hc->xfer_count;
	if (remaining_count > hc->max_packet) {
		byte_count = hc->max_packet;
	} else {
		byte_count = remaining_count;
	}

	dword_count = (byte_count + 3) / 4;

	if ((((unsigned long)data_buff) & 0x3) == 0) {
		/* xfer_buff is DWORD aligned. */
		for (i = 0; i < dword_count; i++, data_buff++) {
			DWC_WRITE_REG32(data_fifo, *data_buff);
		}
	} else {
		/* xfer_buff is not DWORD aligned. */
		for (i = 0; i < dword_count; i++, data_buff++) {
			uint32_t data;
			data =
			    (data_buff[0] | data_buff[1] << 8 | data_buff[2] <<
			     16 | data_buff[3] << 24);
			DWC_WRITE_REG32(data_fifo, data);
		}
	}

	hc->xfer_count += byte_count;
	hc->xfer_buff += byte_count;
}
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
typedef  int /*<<< orphan*/  u16 ;
struct pch_spi_data {int bpw_len; int* pkt_rx_buff; TYPE_1__* cur_trans; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rx_buf; } ;

/* Variables and functions */

__attribute__((used)) static void pch_spi_copy_rx_data(struct pch_spi_data *data, int bpw)
{
	int j;
	u8 *rx_buf;
	u16 *rx_sbuf;

	/* copy Rx Data */
	if (!data->cur_trans->rx_buf)
		return;

	if (bpw == 8) {
		rx_buf = data->cur_trans->rx_buf;
		for (j = 0; j < data->bpw_len; j++)
			*rx_buf++ = data->pkt_rx_buff[j] & 0xFF;
	} else {
		rx_sbuf = data->cur_trans->rx_buf;
		for (j = 0; j < data->bpw_len; j++)
			*rx_sbuf++ = data->pkt_rx_buff[j];
	}
}
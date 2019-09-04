#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  complete; struct mcr20a_local* context; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct mcr20a_local {TYPE_1__ rx_buf_msg; TYPE_2__ rx_xfer_lqi; TYPE_2__ rx_xfer_buf; TYPE_2__ rx_xfer_header; int /*<<< orphan*/  rx_lqi; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  rx_header; TYPE_1__ reg_msg; TYPE_2__ reg_xfer_data; TYPE_2__ reg_xfer_cmd; int /*<<< orphan*/  reg_data; int /*<<< orphan*/  reg_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcr20a_handle_rx_read_buf_complete ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  spi_message_init (TYPE_1__*) ; 

__attribute__((used)) static void
mcr20a_setup_rx_spi_messages(struct mcr20a_local *lp)
{
	spi_message_init(&lp->reg_msg);
	lp->reg_msg.context = lp;

	lp->reg_xfer_cmd.len = 1;
	lp->reg_xfer_cmd.tx_buf = lp->reg_cmd;
	lp->reg_xfer_cmd.rx_buf = lp->reg_cmd;

	lp->reg_xfer_data.rx_buf = lp->reg_data;
	lp->reg_xfer_data.tx_buf = lp->reg_data;

	spi_message_add_tail(&lp->reg_xfer_cmd, &lp->reg_msg);
	spi_message_add_tail(&lp->reg_xfer_data, &lp->reg_msg);

	spi_message_init(&lp->rx_buf_msg);
	lp->rx_buf_msg.context = lp;
	lp->rx_buf_msg.complete = mcr20a_handle_rx_read_buf_complete;
	lp->rx_xfer_header.len = 1;
	lp->rx_xfer_header.tx_buf = lp->rx_header;
	lp->rx_xfer_header.rx_buf = lp->rx_header;

	lp->rx_xfer_buf.rx_buf = lp->rx_buf;

	lp->rx_xfer_lqi.len = 1;
	lp->rx_xfer_lqi.rx_buf = lp->rx_lqi;

	spi_message_add_tail(&lp->rx_xfer_header, &lp->rx_buf_msg);
	spi_message_add_tail(&lp->rx_xfer_buf, &lp->rx_buf_msg);
	spi_message_add_tail(&lp->rx_xfer_lqi, &lp->rx_buf_msg);
}
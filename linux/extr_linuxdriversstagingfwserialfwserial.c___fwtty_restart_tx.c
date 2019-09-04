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
struct fwtty_port {int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  drain; } ;

/* Variables and functions */
 int dma_fifo_avail (int /*<<< orphan*/ *) ; 
 int dma_fifo_out_level (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,int,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __fwtty_restart_tx(struct fwtty_port *port)
{
	int len, avail;

	len = dma_fifo_out_level(&port->tx_fifo);
	if (len)
		schedule_delayed_work(&port->drain, 0);
	avail = dma_fifo_avail(&port->tx_fifo);

	fwtty_dbg(port, "fifo len: %d avail: %d\n", len, avail);
}
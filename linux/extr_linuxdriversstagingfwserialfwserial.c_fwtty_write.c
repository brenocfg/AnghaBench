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
struct tty_struct {struct fwtty_port* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  writes; } ;
struct fwtty_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  drain; int /*<<< orphan*/  tx_fifo; TYPE_1__ stats; } ;

/* Variables and functions */
 int DRAIN_THRESHOLD ; 
 int /*<<< orphan*/  debug_short_write (struct fwtty_port*,int,int) ; 
 int dma_fifo_in (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int dma_fifo_out_level (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,int) ; 
 int /*<<< orphan*/  fwtty_profile_data (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fwtty_tx (struct fwtty_port*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fwtty_write(struct tty_struct *tty, const unsigned char *buf, int c)
{
	struct fwtty_port *port = tty->driver_data;
	int n, len;

	fwtty_dbg(port, "%d\n", c);
	fwtty_profile_data(port->stats.writes, c);

	spin_lock_bh(&port->lock);
	n = dma_fifo_in(&port->tx_fifo, buf, c);
	len = dma_fifo_out_level(&port->tx_fifo);
	if (len < DRAIN_THRESHOLD)
		schedule_delayed_work(&port->drain, 1);
	spin_unlock_bh(&port->lock);

	if (len >= DRAIN_THRESHOLD)
		fwtty_tx(port, false);

	debug_short_write(port, c, n);

	return (n < 0) ? 0 : n;
}
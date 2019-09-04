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
struct tty_struct {struct fwtty_port* driver_data; } ;
struct fwtty_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_fifo; } ;

/* Variables and functions */
 int dma_fifo_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fwtty_write_room(struct tty_struct *tty)
{
	struct fwtty_port *port = tty->driver_data;
	int n;

	spin_lock_bh(&port->lock);
	n = dma_fifo_avail(&port->tx_fifo);
	spin_unlock_bh(&port->lock);

	fwtty_dbg(port, "%d\n", n);

	return n;
}
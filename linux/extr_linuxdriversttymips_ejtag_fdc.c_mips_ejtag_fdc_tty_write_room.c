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
struct tty_struct {struct mips_ejtag_fdc_tty_port* driver_data; } ;
struct mips_ejtag_fdc_tty_port {int xmit_cnt; int /*<<< orphan*/  xmit_lock; struct mips_ejtag_fdc_tty* driver; } ;
struct mips_ejtag_fdc_tty {int xmit_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mips_ejtag_fdc_tty_write_room(struct tty_struct *tty)
{
	struct mips_ejtag_fdc_tty_port *dport = tty->driver_data;
	struct mips_ejtag_fdc_tty *priv = dport->driver;
	int room;

	/* Report the space in the xmit buffer */
	spin_lock(&dport->xmit_lock);
	room = priv->xmit_size - dport->xmit_cnt;
	spin_unlock(&dport->xmit_lock);

	return room;
}
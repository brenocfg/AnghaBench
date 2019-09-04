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
struct mips_ejtag_fdc_tty_port {int xmit_cnt; int /*<<< orphan*/  xmit_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mips_ejtag_fdc_tty_chars_in_buffer(struct tty_struct *tty)
{
	struct mips_ejtag_fdc_tty_port *dport = tty->driver_data;
	int chars;

	/* Report the number of bytes in the xmit buffer */
	spin_lock(&dport->xmit_lock);
	chars = dport->xmit_cnt;
	spin_unlock(&dport->xmit_lock);

	return chars;
}
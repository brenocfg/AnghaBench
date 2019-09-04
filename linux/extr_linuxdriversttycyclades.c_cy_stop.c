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
struct tty_struct {int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct cyclades_port {int line; struct cyclades_card* card; } ;
struct cyclades_card {int first_line; int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CyCAR ; 
 int /*<<< orphan*/  CySRER ; 
 int CyTxRdy ; 
 int /*<<< orphan*/  cy_is_Z (struct cyclades_card*) ; 
 int cyy_readb (struct cyclades_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyy_writeb (struct cyclades_port*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cy_stop(struct tty_struct *tty)
{
	struct cyclades_card *cinfo;
	struct cyclades_port *info = tty->driver_data;
	int channel;
	unsigned long flags;

#ifdef CY_DEBUG_OTHER
	printk(KERN_DEBUG "cyc:cy_stop ttyC%d\n", info->line);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_stop"))
		return;

	cinfo = info->card;
	channel = info->line - cinfo->first_line;
	if (!cy_is_Z(cinfo)) {
		spin_lock_irqsave(&cinfo->card_lock, flags);
		cyy_writeb(info, CyCAR, channel & 0x03);
		cyy_writeb(info, CySRER, cyy_readb(info, CySRER) & ~CyTxRdy);
		spin_unlock_irqrestore(&cinfo->card_lock, flags);
	}
}
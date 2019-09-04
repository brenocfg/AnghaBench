#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {unsigned char* xmit_buf; int /*<<< orphan*/  delta_msr_wait; } ;
struct cyclades_port {TYPE_1__ port; struct cyclades_card* card; } ;
struct cyclades_card {int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 scalar_t__ C_HUPCL (struct tty_struct*) ; 
 int CyCHAN_CTL ; 
 int CyDIS_RCVR ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  cy_is_Z (struct cyclades_card*) ; 
 int /*<<< orphan*/  cyy_change_rts_dtr (struct cyclades_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cyy_issue_cmd (struct cyclades_port*,int) ; 
 int /*<<< orphan*/  cyz_is_loaded (struct cyclades_card*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_initialized (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_port_lower_dtr_rts (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cy_shutdown(struct cyclades_port *info, struct tty_struct *tty)
{
	struct cyclades_card *card;
	unsigned long flags;

	if (!tty_port_initialized(&info->port))
		return;

	card = info->card;
	if (!cy_is_Z(card)) {
		spin_lock_irqsave(&card->card_lock, flags);

		/* Clear delta_msr_wait queue to avoid mem leaks. */
		wake_up_interruptible(&info->port.delta_msr_wait);

		if (info->port.xmit_buf) {
			unsigned char *temp;
			temp = info->port.xmit_buf;
			info->port.xmit_buf = NULL;
			free_page((unsigned long)temp);
		}
		if (C_HUPCL(tty))
			cyy_change_rts_dtr(info, 0, TIOCM_RTS | TIOCM_DTR);

		cyy_issue_cmd(info, CyCHAN_CTL | CyDIS_RCVR);
		/* it may be appropriate to clear _XMIT at
		   some later date (after testing)!!! */

		set_bit(TTY_IO_ERROR, &tty->flags);
		tty_port_set_initialized(&info->port, 0);
		spin_unlock_irqrestore(&card->card_lock, flags);
	} else {
#ifdef CY_DEBUG_OPEN
		int channel = info->line - card->first_line;
		printk(KERN_DEBUG "cyc shutdown Z card %d, channel %d, "
			"base_addr %p\n", card, channel, card->base_addr);
#endif

		if (!cyz_is_loaded(card))
			return;

		spin_lock_irqsave(&card->card_lock, flags);

		if (info->port.xmit_buf) {
			unsigned char *temp;
			temp = info->port.xmit_buf;
			info->port.xmit_buf = NULL;
			free_page((unsigned long)temp);
		}

		if (C_HUPCL(tty))
			tty_port_lower_dtr_rts(&info->port);

		set_bit(TTY_IO_ERROR, &tty->flags);
		tty_port_set_initialized(&info->port, 0);

		spin_unlock_irqrestore(&card->card_lock, flags);
	}

#ifdef CY_DEBUG_OPEN
	printk(KERN_DEBUG "cyc shutdown done\n");
#endif
}
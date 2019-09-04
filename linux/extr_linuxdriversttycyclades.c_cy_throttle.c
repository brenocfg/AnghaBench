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
struct cyclades_port {int throttle; struct cyclades_card* card; } ;
struct cyclades_card {int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  TIOCM_RTS ; 
 int /*<<< orphan*/  cy_is_Z (struct cyclades_card*) ; 
 int /*<<< orphan*/  cy_send_xchar (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyy_change_rts_dtr (struct cyclades_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cy_throttle(struct tty_struct *tty)
{
	struct cyclades_port *info = tty->driver_data;
	struct cyclades_card *card;
	unsigned long flags;

#ifdef CY_DEBUG_THROTTLE
	printk(KERN_DEBUG "cyc:throttle %s ...ttyC%d\n", tty_name(tty),
			 info->line);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_throttle"))
		return;

	card = info->card;

	if (I_IXOFF(tty)) {
		if (!cy_is_Z(card))
			cy_send_xchar(tty, STOP_CHAR(tty));
		else
			info->throttle = 1;
	}

	if (C_CRTSCTS(tty)) {
		if (!cy_is_Z(card)) {
			spin_lock_irqsave(&card->card_lock, flags);
			cyy_change_rts_dtr(info, 0, TIOCM_RTS);
			spin_unlock_irqrestore(&card->card_lock, flags);
		} else {
			info->throttle = 1;
		}
	}
}
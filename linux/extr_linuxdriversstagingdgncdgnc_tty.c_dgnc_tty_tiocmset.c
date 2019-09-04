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
struct un_t {struct channel_t* un_ch; } ;
struct tty_struct {struct un_t* driver_data; } ;
struct dgnc_board {TYPE_1__* bd_ops; } ;
struct channel_t {int /*<<< orphan*/  ch_lock; int /*<<< orphan*/  ch_mostat; struct dgnc_board* ch_bd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* assert_modem_signals ) (struct channel_t*) ;} ;

/* Variables and functions */
 int EIO ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  UART_MCR_DTR ; 
 int /*<<< orphan*/  UART_MCR_RTS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct channel_t*) ; 

__attribute__((used)) static int dgnc_tty_tiocmset(struct tty_struct *tty,
			     unsigned int set, unsigned int clear)
{
	struct dgnc_board *bd;
	struct channel_t *ch;
	struct un_t *un;
	unsigned long flags;

	if (!tty)
		return -EIO;

	un = tty->driver_data;
	if (!un)
		return -EIO;

	ch = un->un_ch;
	if (!ch)
		return -EIO;

	bd = ch->ch_bd;
	if (!bd)
		return -EIO;

	spin_lock_irqsave(&ch->ch_lock, flags);

	if (set & TIOCM_RTS)
		ch->ch_mostat |= UART_MCR_RTS;

	if (set & TIOCM_DTR)
		ch->ch_mostat |= UART_MCR_DTR;

	if (clear & TIOCM_RTS)
		ch->ch_mostat &= ~(UART_MCR_RTS);

	if (clear & TIOCM_DTR)
		ch->ch_mostat &= ~(UART_MCR_DTR);

	bd->bd_ops->assert_modem_signals(ch);

	spin_unlock_irqrestore(&ch->ch_lock, flags);

	return 0;
}
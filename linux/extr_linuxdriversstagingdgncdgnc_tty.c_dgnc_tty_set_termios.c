#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct un_t {struct channel_t* un_ch; } ;
struct TYPE_3__ {int /*<<< orphan*/ * c_cc; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; int /*<<< orphan*/  c_cflag; } ;
struct tty_struct {TYPE_1__ termios; struct un_t* driver_data; } ;
struct ktermios {int dummy; } ;
struct dgnc_board {TYPE_2__* bd_ops; } ;
struct channel_t {int /*<<< orphan*/  ch_lock; int /*<<< orphan*/  ch_stopc; int /*<<< orphan*/  ch_startc; int /*<<< orphan*/  ch_c_lflag; int /*<<< orphan*/  ch_c_oflag; int /*<<< orphan*/  ch_c_iflag; int /*<<< orphan*/  ch_c_cflag; struct dgnc_board* ch_bd; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* param ) (struct tty_struct*) ;} ;

/* Variables and functions */
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  dgnc_carrier (struct channel_t*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 

__attribute__((used)) static void dgnc_tty_set_termios(struct tty_struct *tty,
				 struct ktermios *old_termios)
{
	struct dgnc_board *bd;
	struct channel_t *ch;
	struct un_t *un;
	unsigned long flags;

	if (!tty)
		return;

	un = tty->driver_data;
	if (!un)
		return;

	ch = un->un_ch;
	if (!ch)
		return;

	bd = ch->ch_bd;
	if (!bd)
		return;

	spin_lock_irqsave(&ch->ch_lock, flags);

	ch->ch_c_cflag   = tty->termios.c_cflag;
	ch->ch_c_iflag   = tty->termios.c_iflag;
	ch->ch_c_oflag   = tty->termios.c_oflag;
	ch->ch_c_lflag   = tty->termios.c_lflag;
	ch->ch_startc = tty->termios.c_cc[VSTART];
	ch->ch_stopc  = tty->termios.c_cc[VSTOP];

	bd->bd_ops->param(tty);
	dgnc_carrier(ch);

	spin_unlock_irqrestore(&ch->ch_lock, flags);
}
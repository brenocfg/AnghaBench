#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct un_t {struct channel_t* un_ch; } ;
struct tty_struct {struct un_t* driver_data; } ;
struct TYPE_8__ {int un_flags; int /*<<< orphan*/  un_flags_wait; } ;
struct TYPE_7__ {int un_flags; int /*<<< orphan*/  un_flags_wait; } ;
struct channel_t {int /*<<< orphan*/  ch_lock; TYPE_4__ ch_pun; TYPE_3__ ch_tun; TYPE_2__* ch_bd; int /*<<< orphan*/  ch_w_tail; int /*<<< orphan*/  ch_w_head; int /*<<< orphan*/  ch_flags; } ;
struct TYPE_6__ {TYPE_1__* bd_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* flush_uart_write ) (struct channel_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CH_STOP ; 
 int UN_EMPTY ; 
 int UN_LOW ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct channel_t*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dgnc_tty_flush_buffer(struct tty_struct *tty)
{
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

	spin_lock_irqsave(&ch->ch_lock, flags);

	ch->ch_flags &= ~CH_STOP;

	/* Flush our write queue */
	ch->ch_w_head = ch->ch_w_tail;

	/* Flush UARTs transmit FIFO */
	ch->ch_bd->bd_ops->flush_uart_write(ch);

	if (ch->ch_tun.un_flags & (UN_LOW | UN_EMPTY)) {
		ch->ch_tun.un_flags &= ~(UN_LOW | UN_EMPTY);
		wake_up_interruptible(&ch->ch_tun.un_flags_wait);
	}
	if (ch->ch_pun.un_flags & (UN_LOW | UN_EMPTY)) {
		ch->ch_pun.un_flags &= ~(UN_LOW | UN_EMPTY);
		wake_up_interruptible(&ch->ch_pun.un_flags_wait);
	}

	spin_unlock_irqrestore(&ch->ch_lock, flags);
}
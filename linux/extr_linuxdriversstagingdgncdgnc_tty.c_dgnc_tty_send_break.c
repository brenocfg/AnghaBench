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
struct channel_t {int /*<<< orphan*/  ch_lock; struct dgnc_board* ch_bd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_break ) (struct channel_t*,int) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct channel_t*,int) ; 

__attribute__((used)) static int dgnc_tty_send_break(struct tty_struct *tty, int msec)
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

	if (msec < 0)
		msec = 0xFFFF;

	spin_lock_irqsave(&ch->ch_lock, flags);

	bd->bd_ops->send_break(ch, msec);

	spin_unlock_irqrestore(&ch->ch_lock, flags);

	return 0;
}
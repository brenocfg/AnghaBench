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
struct un_t {struct channel_t* un_ch; } ;
struct tty_struct {struct un_t* driver_data; } ;
struct dgnc_board {int dummy; } ;
struct channel_t {int /*<<< orphan*/  ch_lock; int /*<<< orphan*/  ch_flags; struct dgnc_board* ch_bd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_FORCED_STOP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dgnc_tty_start(struct tty_struct *tty)
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

	ch->ch_flags &= ~(CH_FORCED_STOP);

	spin_unlock_irqrestore(&ch->ch_lock, flags);
}
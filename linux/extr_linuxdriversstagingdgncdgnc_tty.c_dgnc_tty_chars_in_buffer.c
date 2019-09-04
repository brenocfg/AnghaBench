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
typedef  int ushort ;
typedef  int uint ;
struct un_t {struct channel_t* un_ch; } ;
struct tty_struct {struct un_t* driver_data; } ;
struct channel_t {int ch_w_head; int ch_w_tail; int /*<<< orphan*/  ch_lock; } ;

/* Variables and functions */
 int WQUEUEMASK ; 
 int WQUEUESIZE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dgnc_tty_chars_in_buffer(struct tty_struct *tty)
{
	struct channel_t *ch = NULL;
	struct un_t *un = NULL;
	ushort thead;
	ushort ttail;
	uint tmask;
	uint chars;
	unsigned long flags;

	if (!tty)
		return 0;

	un = tty->driver_data;
	if (!un)
		return 0;

	ch = un->un_ch;
	if (!ch)
		return 0;

	spin_lock_irqsave(&ch->ch_lock, flags);

	tmask = WQUEUEMASK;
	thead = ch->ch_w_head & tmask;
	ttail = ch->ch_w_tail & tmask;

	spin_unlock_irqrestore(&ch->ch_lock, flags);

	if (ttail == thead)
		chars = 0;
	else if (thead > ttail)
		chars = thead - ttail;
	else
		chars = thead - ttail + WQUEUESIZE;

	return chars;
}
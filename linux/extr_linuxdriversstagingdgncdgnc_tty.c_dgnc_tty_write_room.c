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
typedef  int ushort ;
struct un_t {scalar_t__ un_type; struct channel_t* un_ch; } ;
struct tty_struct {struct un_t* driver_data; } ;
struct TYPE_2__ {scalar_t__ digi_offlen; scalar_t__ digi_onlen; } ;
struct channel_t {int ch_w_head; int ch_w_tail; int ch_flags; int /*<<< orphan*/  ch_lock; TYPE_1__ ch_digi; } ;

/* Variables and functions */
 int CH_PRON ; 
 scalar_t__ DGNC_PRINT ; 
 int WQUEUEMASK ; 
 scalar_t__ WQUEUESIZE ; 
 int dgnc_maxcps_room (struct channel_t*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dgnc_tty_write_room(struct tty_struct *tty)
{
	struct channel_t *ch = NULL;
	struct un_t *un = NULL;
	ushort head;
	ushort tail;
	ushort tmask;
	int room = 0;
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
	head = (ch->ch_w_head) & tmask;
	tail = (ch->ch_w_tail) & tmask;

	room = tail - head - 1;
	if (room < 0)
		room += WQUEUESIZE;

	/* Limit printer to maxcps */
	if (un->un_type != DGNC_PRINT)
		room = dgnc_maxcps_room(ch, room);

	/*
	 * If we are printer device, leave room for
	 * possibly both the on and off strings.
	 */
	if (un->un_type == DGNC_PRINT) {
		if (!(ch->ch_flags & CH_PRON))
			room -= ch->ch_digi.digi_onlen;
		room -= ch->ch_digi.digi_offlen;
	} else {
		if (ch->ch_flags & CH_PRON)
			room -= ch->ch_digi.digi_offlen;
	}

	if (room < 0)
		room = 0;

	spin_unlock_irqrestore(&ch->ch_lock, flags);
	return room;
}
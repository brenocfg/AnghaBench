#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort ;
typedef  int uint ;
struct un_t {scalar_t__ un_type; struct channel_t* un_ch; } ;
struct tty_struct {struct un_t* driver_data; } ;
struct TYPE_4__ {int digi_maxcps; scalar_t__ digi_bufsize; scalar_t__ digi_offlen; int /*<<< orphan*/  digi_offstr; scalar_t__ digi_onlen; int /*<<< orphan*/  digi_onstr; } ;
struct channel_t {int ch_w_head; int ch_w_tail; int ch_flags; int ch_cpstime; int /*<<< orphan*/  ch_lock; TYPE_3__* ch_bd; TYPE_1__ ch_digi; scalar_t__ ch_wqueue; } ;
struct TYPE_6__ {TYPE_2__* bd_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* copy_data_from_queue_to_uart ) (struct channel_t*) ;} ;

/* Variables and functions */
 int CH_PRON ; 
 scalar_t__ DGNC_PRINT ; 
 int HZ ; 
 int WQUEUEMASK ; 
 int WQUEUESIZE ; 
 int dgnc_maxcps_room (struct channel_t*,int) ; 
 int /*<<< orphan*/  dgnc_wmove (struct channel_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct channel_t*) ; 

__attribute__((used)) static int dgnc_tty_write(struct tty_struct *tty,
			  const unsigned char *buf, int count)
{
	struct channel_t *ch = NULL;
	struct un_t *un = NULL;
	int bufcount = 0, n = 0;
	unsigned long flags;
	ushort head;
	ushort tail;
	ushort tmask;
	uint remain;

	if (!tty)
		return 0;

	un = tty->driver_data;
	if (!un)
		return 0;

	ch = un->un_ch;
	if (!ch)
		return 0;

	if (!count)
		return 0;

	/*
	 * Store original amount of characters passed in.
	 * This helps to figure out if we should ask the FEP
	 * to send us an event when it has more space available.
	 */

	spin_lock_irqsave(&ch->ch_lock, flags);

	tmask = WQUEUEMASK;
	head = (ch->ch_w_head) & tmask;
	tail = (ch->ch_w_tail) & tmask;

	bufcount = tail - head - 1;
	if (bufcount < 0)
		bufcount += WQUEUESIZE;

	/*
	 * Limit printer output to maxcps overall, with bursts allowed
	 * up to bufsize characters.
	 */
	if (un->un_type != DGNC_PRINT)
		bufcount = dgnc_maxcps_room(ch, bufcount);

	count = min(count, bufcount);
	if (count <= 0)
		goto exit_retry;

	/*
	 * Output the printer ON string, if we are in terminal mode, but
	 * need to be in printer mode.
	 */
	if ((un->un_type == DGNC_PRINT) && !(ch->ch_flags & CH_PRON)) {
		dgnc_wmove(ch, ch->ch_digi.digi_onstr,
			   (int)ch->ch_digi.digi_onlen);
		head = (ch->ch_w_head) & tmask;
		ch->ch_flags |= CH_PRON;
	}

	/*
	 * On the other hand, output the printer OFF string, if we are
	 * currently in printer mode, but need to output to the terminal.
	 */
	if ((un->un_type != DGNC_PRINT) && (ch->ch_flags & CH_PRON)) {
		dgnc_wmove(ch, ch->ch_digi.digi_offstr,
			   (int)ch->ch_digi.digi_offlen);
		head = (ch->ch_w_head) & tmask;
		ch->ch_flags &= ~CH_PRON;
	}

	n = count;

	/*
	 * If the write wraps over the top of the circular buffer,
	 * move the portion up to the wrap point, and reset the
	 * pointers to the bottom.
	 */
	remain = WQUEUESIZE - head;

	if (n >= remain) {
		n -= remain;
		memcpy(ch->ch_wqueue + head, buf, remain);
		head = 0;
		buf += remain;
	}

	if (n > 0) {
		/* Move rest of data. */
		remain = n;
		memcpy(ch->ch_wqueue + head, buf, remain);
		head += remain;
	}

	if (count) {
		head &= tmask;
		ch->ch_w_head = head;
	}

	/* Update printer buffer empty time. */
	if ((un->un_type == DGNC_PRINT) && (ch->ch_digi.digi_maxcps > 0) &&
	    (ch->ch_digi.digi_bufsize > 0)) {
		ch->ch_cpstime += (HZ * count) / ch->ch_digi.digi_maxcps;
	}

	spin_unlock_irqrestore(&ch->ch_lock, flags);

	if (count)
		ch->ch_bd->bd_ops->copy_data_from_queue_to_uart(ch);

	return count;

exit_retry:
	spin_unlock_irqrestore(&ch->ch_lock, flags);

	return 0;
}
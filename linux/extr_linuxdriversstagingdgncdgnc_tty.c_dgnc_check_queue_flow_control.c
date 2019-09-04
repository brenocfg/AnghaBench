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
struct TYPE_4__ {int digi_flags; } ;
struct channel_t {int ch_r_tail; int ch_r_head; int ch_c_cflag; int ch_flags; int ch_c_iflag; scalar_t__ ch_stops_sent; TYPE_3__* ch_bd; TYPE_1__ ch_digi; } ;
struct TYPE_6__ {TYPE_2__* bd_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* send_start_character ) (struct channel_t*) ;int /*<<< orphan*/  (* enable_receiver ) (struct channel_t*) ;int /*<<< orphan*/  (* send_stop_character ) (struct channel_t*) ;int /*<<< orphan*/  (* disable_receiver ) (struct channel_t*) ;} ;

/* Variables and functions */
 int CH_RECEIVER_OFF ; 
 int CRTSCTS ; 
 int CTSPACE ; 
 int IXOFF ; 
 scalar_t__ MAX_STOPS_SENT ; 
 scalar_t__ RQUEUEMASK ; 
 int RQUEUESIZE ; 
 int RTSPACE ; 
 int /*<<< orphan*/  stub1 (struct channel_t*) ; 
 int /*<<< orphan*/  stub2 (struct channel_t*) ; 
 int /*<<< orphan*/  stub3 (struct channel_t*) ; 
 int /*<<< orphan*/  stub4 (struct channel_t*) ; 

void dgnc_check_queue_flow_control(struct channel_t *ch)
{
	int qleft;

	qleft = ch->ch_r_tail - ch->ch_r_head - 1;
	if (qleft < 0)
		qleft += RQUEUEMASK + 1;

	/*
	 * Check to see if we should enforce flow control on our queue because
	 * the ld (or user) isn't reading data out of our queue fast enuf.
	 *
	 * NOTE: This is done based on what the current flow control of the
	 * port is set for.
	 *
	 * 1) HWFLOW (RTS) - Turn off the UART's Receive interrupt.
	 *	This will cause the UART's FIFO to back up, and force
	 *	the RTS signal to be dropped.
	 * 2) SWFLOW (IXOFF) - Keep trying to send a stop character to
	 *	the other side, in hopes it will stop sending data to us.
	 * 3) NONE - Nothing we can do.  We will simply drop any extra data
	 *	that gets sent into us when the queue fills up.
	 */
	if (qleft < 256) {
		/* HWFLOW */
		if (ch->ch_digi.digi_flags & CTSPACE ||
		    ch->ch_c_cflag & CRTSCTS) {
			if (!(ch->ch_flags & CH_RECEIVER_OFF)) {
				ch->ch_bd->bd_ops->disable_receiver(ch);
				ch->ch_flags |= (CH_RECEIVER_OFF);
			}
		}
		/* SWFLOW */
		else if (ch->ch_c_iflag & IXOFF) {
			if (ch->ch_stops_sent <= MAX_STOPS_SENT) {
				ch->ch_bd->bd_ops->send_stop_character(ch);
				ch->ch_stops_sent++;
			}
		}
	}

	/*
	 * Check to see if we should unenforce flow control because
	 * ld (or user) finally read enuf data out of our queue.
	 *
	 * NOTE: This is done based on what the current flow control of the
	 * port is set for.
	 *
	 * 1) HWFLOW (RTS) - Turn back on the UART's Receive interrupt.
	 *	This will cause the UART's FIFO to raise RTS back up,
	 *	which will allow the other side to start sending data again.
	 * 2) SWFLOW (IXOFF) - Send a start character to
	 *	the other side, so it will start sending data to us again.
	 * 3) NONE - Do nothing. Since we didn't do anything to turn off the
	 *	other side, we don't need to do anything now.
	 */
	if (qleft > (RQUEUESIZE / 2)) {
		/* HWFLOW */
		if (ch->ch_digi.digi_flags & RTSPACE ||
		    ch->ch_c_cflag & CRTSCTS) {
			if (ch->ch_flags & CH_RECEIVER_OFF) {
				ch->ch_bd->bd_ops->enable_receiver(ch);
				ch->ch_flags &= ~(CH_RECEIVER_OFF);
			}
		}
		/* SWFLOW */
		else if (ch->ch_c_iflag & IXOFF && ch->ch_stops_sent) {
			ch->ch_stops_sent = 0;
			ch->ch_bd->bd_ops->send_start_character(ch);
		}
	}
}
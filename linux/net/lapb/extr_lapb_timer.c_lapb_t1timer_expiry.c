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
struct timer_list {int dummy; } ;
struct lapb_cb {int state; int mode; int /*<<< orphan*/  n2count; int /*<<< orphan*/  dev; int /*<<< orphan*/  n2; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAPB_COMMAND ; 
 int LAPB_DCE ; 
 int /*<<< orphan*/  LAPB_DISC ; 
 int /*<<< orphan*/  LAPB_DM ; 
 int LAPB_EXTENDED ; 
 int /*<<< orphan*/  LAPB_POLLOFF ; 
 int /*<<< orphan*/  LAPB_POLLON ; 
 int /*<<< orphan*/  LAPB_RESPONSE ; 
 int /*<<< orphan*/  LAPB_SABM ; 
 int /*<<< orphan*/  LAPB_SABME ; 
#define  LAPB_STATE_0 132 
#define  LAPB_STATE_1 131 
#define  LAPB_STATE_2 130 
#define  LAPB_STATE_3 129 
#define  LAPB_STATE_4 128 
 int /*<<< orphan*/  LAPB_TIMEDOUT ; 
 struct lapb_cb* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct lapb_cb* lapb ; 
 int /*<<< orphan*/  lapb_clear_queues (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_disconnect_confirmation (struct lapb_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_disconnect_indication (struct lapb_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_kick (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_requeue_frames (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_send_control (struct lapb_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_start_t1timer (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_stop_t2timer (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_transmit_frmr (struct lapb_cb*) ; 
 int /*<<< orphan*/  t1timer ; 

__attribute__((used)) static void lapb_t1timer_expiry(struct timer_list *t)
{
	struct lapb_cb *lapb = from_timer(lapb, t, t1timer);

	switch (lapb->state) {

		/*
		 *	If we are a DCE, keep going DM .. DM .. DM
		 */
		case LAPB_STATE_0:
			if (lapb->mode & LAPB_DCE)
				lapb_send_control(lapb, LAPB_DM, LAPB_POLLOFF, LAPB_RESPONSE);
			break;

		/*
		 *	Awaiting connection state, send SABM(E), up to N2 times.
		 */
		case LAPB_STATE_1:
			if (lapb->n2count == lapb->n2) {
				lapb_clear_queues(lapb);
				lapb->state = LAPB_STATE_0;
				lapb_disconnect_indication(lapb, LAPB_TIMEDOUT);
				lapb_dbg(0, "(%p) S1 -> S0\n", lapb->dev);
				return;
			} else {
				lapb->n2count++;
				if (lapb->mode & LAPB_EXTENDED) {
					lapb_dbg(1, "(%p) S1 TX SABME(1)\n",
						 lapb->dev);
					lapb_send_control(lapb, LAPB_SABME, LAPB_POLLON, LAPB_COMMAND);
				} else {
					lapb_dbg(1, "(%p) S1 TX SABM(1)\n",
						 lapb->dev);
					lapb_send_control(lapb, LAPB_SABM, LAPB_POLLON, LAPB_COMMAND);
				}
			}
			break;

		/*
		 *	Awaiting disconnection state, send DISC, up to N2 times.
		 */
		case LAPB_STATE_2:
			if (lapb->n2count == lapb->n2) {
				lapb_clear_queues(lapb);
				lapb->state = LAPB_STATE_0;
				lapb_disconnect_confirmation(lapb, LAPB_TIMEDOUT);
				lapb_dbg(0, "(%p) S2 -> S0\n", lapb->dev);
				return;
			} else {
				lapb->n2count++;
				lapb_dbg(1, "(%p) S2 TX DISC(1)\n", lapb->dev);
				lapb_send_control(lapb, LAPB_DISC, LAPB_POLLON, LAPB_COMMAND);
			}
			break;

		/*
		 *	Data transfer state, restransmit I frames, up to N2 times.
		 */
		case LAPB_STATE_3:
			if (lapb->n2count == lapb->n2) {
				lapb_clear_queues(lapb);
				lapb->state = LAPB_STATE_0;
				lapb_stop_t2timer(lapb);
				lapb_disconnect_indication(lapb, LAPB_TIMEDOUT);
				lapb_dbg(0, "(%p) S3 -> S0\n", lapb->dev);
				return;
			} else {
				lapb->n2count++;
				lapb_requeue_frames(lapb);
				lapb_kick(lapb);
			}
			break;

		/*
		 *	Frame reject state, restransmit FRMR frames, up to N2 times.
		 */
		case LAPB_STATE_4:
			if (lapb->n2count == lapb->n2) {
				lapb_clear_queues(lapb);
				lapb->state = LAPB_STATE_0;
				lapb_disconnect_indication(lapb, LAPB_TIMEDOUT);
				lapb_dbg(0, "(%p) S4 -> S0\n", lapb->dev);
				return;
			} else {
				lapb->n2count++;
				lapb_transmit_frmr(lapb);
			}
			break;
	}

	lapb_start_t1timer(lapb);
}
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
struct sk_buff {int dummy; } ;
struct lapb_frame {int type; int /*<<< orphan*/  pf; } ;
struct lapb_cb {int /*<<< orphan*/  dev; void* state; } ;

/* Variables and functions */
#define  LAPB_DISC 136 
#define  LAPB_DM 135 
#define  LAPB_I 134 
 int /*<<< orphan*/  LAPB_NOTCONNECTED ; 
 int /*<<< orphan*/  LAPB_OK ; 
#define  LAPB_REJ 133 
 int /*<<< orphan*/  LAPB_RESPONSE ; 
#define  LAPB_RNR 132 
#define  LAPB_RR 131 
#define  LAPB_SABM 130 
#define  LAPB_SABME 129 
 void* LAPB_STATE_0 ; 
#define  LAPB_UA 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lapb_dbg (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  lapb_disconnect_confirmation (struct lapb_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_send_control (struct lapb_cb*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_start_t1timer (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_stop_t2timer (struct lapb_cb*) ; 

__attribute__((used)) static void lapb_state2_machine(struct lapb_cb *lapb, struct sk_buff *skb,
				struct lapb_frame *frame)
{
	switch (frame->type) {
	case LAPB_SABM:
	case LAPB_SABME:
		lapb_dbg(1, "(%p) S2 RX {SABM,SABME}(%d)\n",
			 lapb->dev, frame->pf);
		lapb_dbg(1, "(%p) S2 TX DM(%d)\n", lapb->dev, frame->pf);
		lapb_send_control(lapb, LAPB_DM, frame->pf, LAPB_RESPONSE);
		break;

	case LAPB_DISC:
		lapb_dbg(1, "(%p) S2 RX DISC(%d)\n", lapb->dev, frame->pf);
		lapb_dbg(1, "(%p) S2 TX UA(%d)\n", lapb->dev, frame->pf);
		lapb_send_control(lapb, LAPB_UA, frame->pf, LAPB_RESPONSE);
		break;

	case LAPB_UA:
		lapb_dbg(1, "(%p) S2 RX UA(%d)\n", lapb->dev, frame->pf);
		if (frame->pf) {
			lapb_dbg(0, "(%p) S2 -> S0\n", lapb->dev);
			lapb->state = LAPB_STATE_0;
			lapb_start_t1timer(lapb);
			lapb_stop_t2timer(lapb);
			lapb_disconnect_confirmation(lapb, LAPB_OK);
		}
		break;

	case LAPB_DM:
		lapb_dbg(1, "(%p) S2 RX DM(%d)\n", lapb->dev, frame->pf);
		if (frame->pf) {
			lapb_dbg(0, "(%p) S2 -> S0\n", lapb->dev);
			lapb->state = LAPB_STATE_0;
			lapb_start_t1timer(lapb);
			lapb_stop_t2timer(lapb);
			lapb_disconnect_confirmation(lapb, LAPB_NOTCONNECTED);
		}
		break;

	case LAPB_I:
	case LAPB_REJ:
	case LAPB_RNR:
	case LAPB_RR:
		lapb_dbg(1, "(%p) S2 RX {I,REJ,RNR,RR}(%d)\n",
		       lapb->dev, frame->pf);
		lapb_dbg(1, "(%p) S2 RX DM(%d)\n", lapb->dev, frame->pf);
		if (frame->pf)
			lapb_send_control(lapb, LAPB_DM, frame->pf,
					  LAPB_RESPONSE);
		break;
	}

	kfree_skb(skb);
}
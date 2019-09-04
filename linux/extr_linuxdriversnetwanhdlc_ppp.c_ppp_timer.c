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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int expires; } ;
struct proto {int state; TYPE_1__ timer; int /*<<< orphan*/  dev; int /*<<< orphan*/  pid; int /*<<< orphan*/  restart_counter; } ;
struct ppp {int last_pong; int keepalive_timeout; int keepalive_interval; int /*<<< orphan*/  lock; int /*<<< orphan*/  echo_id; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
#define  ACK_RECV 132 
#define  ACK_SENT 131 
 int HZ ; 
 int /*<<< orphan*/  LCP_ECHO_REQ ; 
#define  OPENED 130 
 int /*<<< orphan*/  PID_LCP ; 
#define  REQ_SENT 129 
 int /*<<< orphan*/  START ; 
 int /*<<< orphan*/  STOP ; 
#define  STOPPING 128 
 int /*<<< orphan*/  TO_BAD ; 
 int /*<<< orphan*/  TO_GOOD ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct proto* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ppp* get_ppp (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppp_cp_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppp_tx_cp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppp_tx_flush () ; 
 struct proto* proto ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  time_after (int,int) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ppp_timer(struct timer_list *t)
{
	struct proto *proto = from_timer(proto, t, timer);
	struct ppp *ppp = get_ppp(proto->dev);
	unsigned long flags;

	spin_lock_irqsave(&ppp->lock, flags);
	switch (proto->state) {
	case STOPPING:
	case REQ_SENT:
	case ACK_RECV:
	case ACK_SENT:
		if (proto->restart_counter) {
			ppp_cp_event(proto->dev, proto->pid, TO_GOOD, 0, 0,
				     0, NULL);
			proto->restart_counter--;
		} else if (netif_carrier_ok(proto->dev))
			ppp_cp_event(proto->dev, proto->pid, TO_GOOD, 0, 0,
				     0, NULL);
		else
			ppp_cp_event(proto->dev, proto->pid, TO_BAD, 0, 0,
				     0, NULL);
		break;

	case OPENED:
		if (proto->pid != PID_LCP)
			break;
		if (time_after(jiffies, ppp->last_pong +
			       ppp->keepalive_timeout * HZ)) {
			netdev_info(proto->dev, "Link down\n");
			ppp_cp_event(proto->dev, PID_LCP, STOP, 0, 0, 0, NULL);
			ppp_cp_event(proto->dev, PID_LCP, START, 0, 0, 0, NULL);
		} else {	/* send keep-alive packet */
			ppp->echo_id = ++ppp->seq;
			ppp_tx_cp(proto->dev, PID_LCP, LCP_ECHO_REQ,
				  ppp->echo_id, 0, NULL);
			proto->timer.expires = jiffies +
				ppp->keepalive_interval * HZ;
			add_timer(&proto->timer);
		}
		break;
	}
	spin_unlock_irqrestore(&ppp->lock, flags);
	ppp_tx_flush();
}
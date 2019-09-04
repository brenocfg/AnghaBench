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
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;
struct proto {int state; int /*<<< orphan*/  timer; void* timeout; scalar_t__ cr_id; scalar_t__ restart_counter; } ;
struct ppp {int req_timeout; int keepalive_interval; void* last_pong; scalar_t__ seq; scalar_t__ cr_retries; scalar_t__ term_retries; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CLOSED ; 
 scalar_t__ CP_CODE_REJ ; 
 scalar_t__ CP_CONF_ACK ; 
 scalar_t__ CP_CONF_REQ ; 
 scalar_t__ CP_TERM_ACK ; 
 scalar_t__ CP_TERM_REQ ; 
 size_t EVENTS ; 
 int HZ ; 
 int IRC ; 
 int OPENED ; 
 size_t PID_IPCP ; 
 size_t PID_IPV6CP ; 
 size_t PID_LCP ; 
 int SCA ; 
 int SCJ ; 
 int SCN ; 
 int SCR ; 
 int STA ; 
 size_t START ; 
 int STATES ; 
 int STATE_MASK ; 
 size_t STOP ; 
 int STOPPING ; 
 int STR ; 
 int ZRC ; 
 int** cp_table ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct ppp* get_ppp (struct net_device*) ; 
 struct proto* get_proto (struct net_device*,size_t) ; 
 void* jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dormant_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant_on (struct net_device*) ; 
 int /*<<< orphan*/  ppp_tx_cp (struct net_device*,size_t,scalar_t__,scalar_t__,unsigned int,void const*) ; 
 int /*<<< orphan*/  proto_name (size_t) ; 

__attribute__((used)) static void ppp_cp_event(struct net_device *dev, u16 pid, u16 event, u8 code,
			 u8 id, unsigned int len, const void *data)
{
	int old_state, action;
	struct ppp *ppp = get_ppp(dev);
	struct proto *proto = get_proto(dev, pid);

	old_state = proto->state;
	BUG_ON(old_state >= STATES);
	BUG_ON(event >= EVENTS);

#if DEBUG_STATE
	printk(KERN_DEBUG "%s: %s ppp_cp_event(%s) %s ...\n", dev->name,
	       proto_name(pid), event_names[event], state_names[proto->state]);
#endif

	action = cp_table[event][old_state];

	proto->state = action & STATE_MASK;
	if (action & (SCR | STR)) /* set Configure-Req/Terminate-Req timer */
		mod_timer(&proto->timer, proto->timeout =
			  jiffies + ppp->req_timeout * HZ);
	if (action & ZRC)
		proto->restart_counter = 0;
	if (action & IRC)
		proto->restart_counter = (proto->state == STOPPING) ?
			ppp->term_retries : ppp->cr_retries;

	if (action & SCR)	/* send Configure-Request */
		ppp_tx_cp(dev, pid, CP_CONF_REQ, proto->cr_id = ++ppp->seq,
			  0, NULL);
	if (action & SCA)	/* send Configure-Ack */
		ppp_tx_cp(dev, pid, CP_CONF_ACK, id, len, data);
	if (action & SCN)	/* send Configure-Nak/Reject */
		ppp_tx_cp(dev, pid, code, id, len, data);
	if (action & STR)	/* send Terminate-Request */
		ppp_tx_cp(dev, pid, CP_TERM_REQ, ++ppp->seq, 0, NULL);
	if (action & STA)	/* send Terminate-Ack */
		ppp_tx_cp(dev, pid, CP_TERM_ACK, id, 0, NULL);
	if (action & SCJ)	/* send Code-Reject */
		ppp_tx_cp(dev, pid, CP_CODE_REJ, ++ppp->seq, len, data);

	if (old_state != OPENED && proto->state == OPENED) {
		netdev_info(dev, "%s up\n", proto_name(pid));
		if (pid == PID_LCP) {
			netif_dormant_off(dev);
			ppp_cp_event(dev, PID_IPCP, START, 0, 0, 0, NULL);
			ppp_cp_event(dev, PID_IPV6CP, START, 0, 0, 0, NULL);
			ppp->last_pong = jiffies;
			mod_timer(&proto->timer, proto->timeout =
				  jiffies + ppp->keepalive_interval * HZ);
		}
	}
	if (old_state == OPENED && proto->state != OPENED) {
		netdev_info(dev, "%s down\n", proto_name(pid));
		if (pid == PID_LCP) {
			netif_dormant_on(dev);
			ppp_cp_event(dev, PID_IPCP, STOP, 0, 0, 0, NULL);
			ppp_cp_event(dev, PID_IPV6CP, STOP, 0, 0, 0, NULL);
		}
	}
	if (old_state != CLOSED && proto->state == CLOSED)
		del_timer(&proto->timer);

#if DEBUG_STATE
	printk(KERN_DEBUG "%s: %s ppp_cp_event(%s) ... %s\n", dev->name,
	       proto_name(pid), event_names[event], state_names[proto->state]);
#endif
}
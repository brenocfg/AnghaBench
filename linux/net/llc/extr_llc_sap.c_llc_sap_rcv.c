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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  destructor; struct sock* sk; } ;
struct llc_sap_state_ev {scalar_t__ reason; int /*<<< orphan*/  type; } ;
struct llc_sap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLC_SAP_EV_TYPE_PDU ; 
 struct llc_sap_state_ev* llc_sap_ev (struct sk_buff*) ; 
 int /*<<< orphan*/  llc_sap_state_process (struct llc_sap*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_efree ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

__attribute__((used)) static void llc_sap_rcv(struct llc_sap *sap, struct sk_buff *skb,
			struct sock *sk)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);

	ev->type   = LLC_SAP_EV_TYPE_PDU;
	ev->reason = 0;
	skb_orphan(skb);
	sock_hold(sk);
	skb->sk = sk;
	skb->destructor = sock_efree;
	llc_sap_state_process(sap, skb);
}
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
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct sk_buff {int dummy; } ;
struct llc_sock {scalar_t__ state; } ;
struct llc_conn_state_trans {scalar_t__ next_state; } ;

/* Variables and functions */
 scalar_t__ NBR_CONN_STATES ; 
 scalar_t__ NO_STATE_CHANGE ; 
 int /*<<< orphan*/  llc_data_accept_state (scalar_t__) ; 
 int llc_exec_conn_trans_actions (struct sock*,struct llc_conn_state_trans*,struct sk_buff*) ; 
 struct llc_conn_state_trans* llc_qualify_conn_ev (struct sock*,struct sk_buff*) ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int llc_conn_service(struct sock *sk, struct sk_buff *skb)
{
	int rc = 1;
	struct llc_sock *llc = llc_sk(sk);
	struct llc_conn_state_trans *trans;

	if (llc->state > NBR_CONN_STATES)
		goto out;
	rc = 0;
	trans = llc_qualify_conn_ev(sk, skb);
	if (trans) {
		rc = llc_exec_conn_trans_actions(sk, trans, skb);
		if (!rc && trans->next_state != NO_STATE_CHANGE) {
			llc->state = trans->next_state;
			if (!llc_data_accept_state(llc->state))
				sk->sk_state_change(sk);
		}
	}
out:
	return rc;
}
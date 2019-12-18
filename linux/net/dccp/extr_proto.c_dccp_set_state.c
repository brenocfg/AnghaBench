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
struct sock {int sk_state; int sk_userlocks; TYPE_1__* sk_prot; } ;
struct TYPE_6__ {int /*<<< orphan*/  dccps_featneg; } ;
struct TYPE_5__ {int /*<<< orphan*/ * icsk_bind_hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* unhash ) (struct sock*) ;} ;

/* Variables and functions */
 int const DCCP_ACTIVE_CLOSEREQ ; 
#define  DCCP_CLOSED 129 
 int const DCCP_CLOSING ; 
 int /*<<< orphan*/  DCCP_DEC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_CURRESTAB ; 
 int /*<<< orphan*/  DCCP_MIB_ESTABRESETS ; 
#define  DCCP_OPEN 128 
 int const DCCP_PARTOPEN ; 
 int SOCK_BINDPORT_LOCK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dccp_feat_list_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dccp_pr_debug (char*,int /*<<< orphan*/ ,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_role (struct sock*) ; 
 TYPE_3__* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_state_name (int const) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_put_port (struct sock*) ; 
 int /*<<< orphan*/  inet_sk_set_state (struct sock*,int const) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

void dccp_set_state(struct sock *sk, const int state)
{
	const int oldstate = sk->sk_state;

	dccp_pr_debug("%s(%p)  %s  -->  %s\n", dccp_role(sk), sk,
		      dccp_state_name(oldstate), dccp_state_name(state));
	WARN_ON(state == oldstate);

	switch (state) {
	case DCCP_OPEN:
		if (oldstate != DCCP_OPEN)
			DCCP_INC_STATS(DCCP_MIB_CURRESTAB);
		/* Client retransmits all Confirm options until entering OPEN */
		if (oldstate == DCCP_PARTOPEN)
			dccp_feat_list_purge(&dccp_sk(sk)->dccps_featneg);
		break;

	case DCCP_CLOSED:
		if (oldstate == DCCP_OPEN || oldstate == DCCP_ACTIVE_CLOSEREQ ||
		    oldstate == DCCP_CLOSING)
			DCCP_INC_STATS(DCCP_MIB_ESTABRESETS);

		sk->sk_prot->unhash(sk);
		if (inet_csk(sk)->icsk_bind_hash != NULL &&
		    !(sk->sk_userlocks & SOCK_BINDPORT_LOCK))
			inet_put_port(sk);
		/* fall through */
	default:
		if (oldstate == DCCP_OPEN)
			DCCP_DEC_STATS(DCCP_MIB_CURRESTAB);
	}

	/* Change state AFTER socket is unhashed to avoid closed
	 * socket sitting in hash tables.
	 */
	inet_sk_set_state(sk, state);
}
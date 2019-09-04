#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_cookie; int /*<<< orphan*/  sk_mark; } ;
struct request_sock {int dummy; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_accept_queue; scalar_t__ icsk_probes_out; scalar_t__ icsk_backoff; scalar_t__ icsk_retransmits; int /*<<< orphan*/ * icsk_bind_hash; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  ir_cookie; int /*<<< orphan*/  ir_mark; int /*<<< orphan*/  ir_num; int /*<<< orphan*/  ir_rmt_port; } ;
struct TYPE_3__ {int /*<<< orphan*/ * mc_list; int /*<<< orphan*/  inet_sport; int /*<<< orphan*/  inet_num; int /*<<< orphan*/  inet_dport; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_RCU_FREE ; 
 int /*<<< orphan*/  TCP_SYN_RECV ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 TYPE_2__* inet_rsk (struct request_sock const*) ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_sk_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_inet_csk_clone (struct sock*,struct request_sock const*) ; 
 struct sock* sk_clone_lock (struct sock const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 

struct sock *inet_csk_clone_lock(const struct sock *sk,
				 const struct request_sock *req,
				 const gfp_t priority)
{
	struct sock *newsk = sk_clone_lock(sk, priority);

	if (newsk) {
		struct inet_connection_sock *newicsk = inet_csk(newsk);

		inet_sk_set_state(newsk, TCP_SYN_RECV);
		newicsk->icsk_bind_hash = NULL;

		inet_sk(newsk)->inet_dport = inet_rsk(req)->ir_rmt_port;
		inet_sk(newsk)->inet_num = inet_rsk(req)->ir_num;
		inet_sk(newsk)->inet_sport = htons(inet_rsk(req)->ir_num);

		/* listeners have SOCK_RCU_FREE, not the children */
		sock_reset_flag(newsk, SOCK_RCU_FREE);

		inet_sk(newsk)->mc_list = NULL;

		newsk->sk_mark = inet_rsk(req)->ir_mark;
		atomic64_set(&newsk->sk_cookie,
			     atomic64_read(&inet_rsk(req)->ir_cookie));

		newicsk->icsk_retransmits = 0;
		newicsk->icsk_backoff	  = 0;
		newicsk->icsk_probes_out  = 0;

		/* Deinitialize accept_queue to trap illegal accesses. */
		memset(&newicsk->icsk_accept_queue, 0, sizeof(newicsk->icsk_accept_queue));

		security_inet_csk_clone(newsk, req);
	}
	return newsk;
}
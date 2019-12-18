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
struct sock {int sk_flags; int /*<<< orphan*/  sk_rxhash; int /*<<< orphan*/  sk_sndtimeo; int /*<<< orphan*/  sk_rcvtimeo; int /*<<< orphan*/  sk_lingertime; int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_sndbuf; TYPE_1__* sk_prot; int /*<<< orphan*/  sk_backlog_rcv; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_family; int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_reuse; int /*<<< orphan*/  sk_no_check_rx; int /*<<< orphan*/  sk_no_check_tx; int /*<<< orphan*/  sk_tsflags; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_type; } ;
struct sctp_sock {int /*<<< orphan*/  reuse; struct sctp_endpoint* ep; } ;
struct sctp_endpoint {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;
struct sctp_association {TYPE_2__ peer; } ;
struct inet_sock {int mc_loop; int mc_ttl; int /*<<< orphan*/ * mc_list; scalar_t__ mc_index; int /*<<< orphan*/  uc_ttl; int /*<<< orphan*/  inet_id; int /*<<< orphan*/  pmtudisc; int /*<<< orphan*/  inet_dport; int /*<<< orphan*/  inet_rcv_saddr; int /*<<< orphan*/  inet_saddr; int /*<<< orphan*/  inet_sport; } ;
struct TYPE_3__ {int /*<<< orphan*/  backlog_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int SK_FLAGS_TIMESTAMP ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  net_enable_timestamp () ; 
 int /*<<< orphan*/  prandom_u32 () ; 
 int /*<<< orphan*/  sctp_destruct_sock ; 
 struct sctp_sock* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  security_sctp_sk_clone (struct sctp_endpoint*,struct sock*,struct sock*) ; 

void sctp_copy_sock(struct sock *newsk, struct sock *sk,
		    struct sctp_association *asoc)
{
	struct inet_sock *inet = inet_sk(sk);
	struct inet_sock *newinet;
	struct sctp_sock *sp = sctp_sk(sk);
	struct sctp_endpoint *ep = sp->ep;

	newsk->sk_type = sk->sk_type;
	newsk->sk_bound_dev_if = sk->sk_bound_dev_if;
	newsk->sk_flags = sk->sk_flags;
	newsk->sk_tsflags = sk->sk_tsflags;
	newsk->sk_no_check_tx = sk->sk_no_check_tx;
	newsk->sk_no_check_rx = sk->sk_no_check_rx;
	newsk->sk_reuse = sk->sk_reuse;
	sctp_sk(newsk)->reuse = sp->reuse;

	newsk->sk_shutdown = sk->sk_shutdown;
	newsk->sk_destruct = sctp_destruct_sock;
	newsk->sk_family = sk->sk_family;
	newsk->sk_protocol = IPPROTO_SCTP;
	newsk->sk_backlog_rcv = sk->sk_prot->backlog_rcv;
	newsk->sk_sndbuf = sk->sk_sndbuf;
	newsk->sk_rcvbuf = sk->sk_rcvbuf;
	newsk->sk_lingertime = sk->sk_lingertime;
	newsk->sk_rcvtimeo = sk->sk_rcvtimeo;
	newsk->sk_sndtimeo = sk->sk_sndtimeo;
	newsk->sk_rxhash = sk->sk_rxhash;

	newinet = inet_sk(newsk);

	/* Initialize sk's sport, dport, rcv_saddr and daddr for
	 * getsockname() and getpeername()
	 */
	newinet->inet_sport = inet->inet_sport;
	newinet->inet_saddr = inet->inet_saddr;
	newinet->inet_rcv_saddr = inet->inet_rcv_saddr;
	newinet->inet_dport = htons(asoc->peer.port);
	newinet->pmtudisc = inet->pmtudisc;
	newinet->inet_id = prandom_u32();

	newinet->uc_ttl = inet->uc_ttl;
	newinet->mc_loop = 1;
	newinet->mc_ttl = 1;
	newinet->mc_index = 0;
	newinet->mc_list = NULL;

	if (newsk->sk_flags & SK_FLAGS_TIMESTAMP)
		net_enable_timestamp();

	/* Set newsk security attributes from orginal sk and connection
	 * security attribute from ep.
	 */
	security_sctp_sk_clone(ep, sk, newsk);
}
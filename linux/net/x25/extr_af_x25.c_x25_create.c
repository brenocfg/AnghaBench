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
struct TYPE_4__ {int /*<<< orphan*/  calling_ae; int /*<<< orphan*/  called_ae; scalar_t__ called_len; scalar_t__ calling_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  reverse; scalar_t__ throughput; void* pacsize_out; void* pacsize_in; void* winsize_out; void* winsize_in; } ;
struct x25_sock {TYPE_2__ dte_facilities; TYPE_1__ facilities; int /*<<< orphan*/  flags; scalar_t__ cudmatchlength; int /*<<< orphan*/  state; int /*<<< orphan*/  t2; int /*<<< orphan*/  t23; int /*<<< orphan*/  t22; int /*<<< orphan*/  t21; } ;
struct socket {scalar_t__ type; int /*<<< orphan*/ * ops; } ;
struct sock {int sk_protocol; int /*<<< orphan*/  sk_backlog_rcv; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ESOCKTNOSUPPORT ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  X25_ACCPT_APPRV_FLAG ; 
 void* X25_DEFAULT_PACKET_SIZE ; 
 int /*<<< orphan*/  X25_DEFAULT_REVERSE ; 
 void* X25_DEFAULT_WINDOW_SIZE ; 
 int /*<<< orphan*/  X25_STATE_0 ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sysctl_x25_ack_holdback_timeout ; 
 int /*<<< orphan*/  sysctl_x25_call_request_timeout ; 
 int /*<<< orphan*/  sysctl_x25_clear_request_timeout ; 
 int /*<<< orphan*/  sysctl_x25_reset_request_timeout ; 
 struct sock* x25_alloc_socket (struct net*,int) ; 
 int /*<<< orphan*/  x25_backlog_rcv ; 
 int /*<<< orphan*/  x25_init_timers (struct sock*) ; 
 int /*<<< orphan*/  x25_proto_ops ; 
 struct x25_sock* x25_sk (struct sock*) ; 

__attribute__((used)) static int x25_create(struct net *net, struct socket *sock, int protocol,
		      int kern)
{
	struct sock *sk;
	struct x25_sock *x25;
	int rc = -EAFNOSUPPORT;

	if (!net_eq(net, &init_net))
		goto out;

	rc = -ESOCKTNOSUPPORT;
	if (sock->type != SOCK_SEQPACKET)
		goto out;

	rc = -EINVAL;
	if (protocol)
		goto out;

	rc = -ENOBUFS;
	if ((sk = x25_alloc_socket(net, kern)) == NULL)
		goto out;

	x25 = x25_sk(sk);

	sock_init_data(sock, sk);

	x25_init_timers(sk);

	sock->ops    = &x25_proto_ops;
	sk->sk_protocol = protocol;
	sk->sk_backlog_rcv = x25_backlog_rcv;

	x25->t21   = sysctl_x25_call_request_timeout;
	x25->t22   = sysctl_x25_reset_request_timeout;
	x25->t23   = sysctl_x25_clear_request_timeout;
	x25->t2    = sysctl_x25_ack_holdback_timeout;
	x25->state = X25_STATE_0;
	x25->cudmatchlength = 0;
	set_bit(X25_ACCPT_APPRV_FLAG, &x25->flags);	/* normally no cud  */
							/* on call accept   */

	x25->facilities.winsize_in  = X25_DEFAULT_WINDOW_SIZE;
	x25->facilities.winsize_out = X25_DEFAULT_WINDOW_SIZE;
	x25->facilities.pacsize_in  = X25_DEFAULT_PACKET_SIZE;
	x25->facilities.pacsize_out = X25_DEFAULT_PACKET_SIZE;
	x25->facilities.throughput  = 0;	/* by default don't negotiate
						   throughput */
	x25->facilities.reverse     = X25_DEFAULT_REVERSE;
	x25->dte_facilities.calling_len = 0;
	x25->dte_facilities.called_len = 0;
	memset(x25->dte_facilities.called_ae, '\0',
			sizeof(x25->dte_facilities.called_ae));
	memset(x25->dte_facilities.calling_ae, '\0',
			sizeof(x25->dte_facilities.calling_ae));

	rc = 0;
out:
	return rc;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/  sk; } ;
struct sock {int /*<<< orphan*/  sk_family; } ;
struct sctp_sock {TYPE_3__* pf; } ;
struct TYPE_6__ {int /*<<< orphan*/  primary_addr; } ;
struct sctp_association {TYPE_2__ peer; } ;
typedef  int /*<<< orphan*/  sctp_assoc_t ;
struct TYPE_8__ {TYPE_1__* nsproxy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* copy_ip_options ) (struct sock*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* to_sk_daddr ) (int /*<<< orphan*/ *,struct sock*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  net_ns; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  SCTP_SOCKET_UDP_HIGH_BANDWIDTH ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int /*<<< orphan*/  UDP ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_copy_sock (int /*<<< orphan*/ ,struct sock*,struct sctp_association*) ; 
 struct sctp_association* sctp_id2assoc (struct sock*,int /*<<< orphan*/ ) ; 
 struct sctp_sock* sctp_sk (struct sock*) ; 
 int sctp_sock_migrate (struct sock*,int /*<<< orphan*/ ,struct sctp_association*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_style (struct sock*,int /*<<< orphan*/ ) ; 
 int sock_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*,int /*<<< orphan*/ ) ; 

int sctp_do_peeloff(struct sock *sk, sctp_assoc_t id, struct socket **sockp)
{
	struct sctp_association *asoc = sctp_id2assoc(sk, id);
	struct sctp_sock *sp = sctp_sk(sk);
	struct socket *sock;
	int err = 0;

	/* Do not peel off from one netns to another one. */
	if (!net_eq(current->nsproxy->net_ns, sock_net(sk)))
		return -EINVAL;

	if (!asoc)
		return -EINVAL;

	/* An association cannot be branched off from an already peeled-off
	 * socket, nor is this supported for tcp style sockets.
	 */
	if (!sctp_style(sk, UDP))
		return -EINVAL;

	/* Create a new socket.  */
	err = sock_create(sk->sk_family, SOCK_SEQPACKET, IPPROTO_SCTP, &sock);
	if (err < 0)
		return err;

	sctp_copy_sock(sock->sk, sk, asoc);

	/* Make peeled-off sockets more like 1-1 accepted sockets.
	 * Set the daddr and initialize id to something more random and also
	 * copy over any ip options.
	 */
	sp->pf->to_sk_daddr(&asoc->peer.primary_addr, sk);
	sp->pf->copy_ip_options(sk, sock->sk);

	/* Populate the fields of the newsk from the oldsk and migrate the
	 * asoc to the newsk.
	 */
	err = sctp_sock_migrate(sk, sock->sk, asoc,
				SCTP_SOCKET_UDP_HIGH_BANDWIDTH);
	if (err) {
		sock_release(sock);
		sock = NULL;
	}

	*sockp = sock;

	return err;
}
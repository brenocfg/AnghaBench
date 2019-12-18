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
struct sock {int sk_max_ack_backlog; } ;
struct sctp_sock {char* sctp_hmac_alg; struct crypto_shash* hmac; struct sctp_endpoint* ep; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;
struct TYPE_5__ {TYPE_1__ bind_addr; } ;
struct sctp_endpoint {TYPE_2__ base; } ;
struct crypto_shash {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  inet_num; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EAGAIN ; 
 int ENOSYS ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int /*<<< orphan*/  PTR_ERR (struct crypto_shash*) ; 
 int /*<<< orphan*/  SCTP_SS_CLOSED ; 
 int /*<<< orphan*/  SCTP_SS_LISTENING ; 
 struct crypto_shash* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_sk_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_autobind (struct sock*) ; 
 scalar_t__ sctp_get_port (struct sock*,int /*<<< orphan*/ ) ; 
 int sctp_hash_endpoint (struct sctp_endpoint*) ; 
 struct sctp_sock* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static int sctp_listen_start(struct sock *sk, int backlog)
{
	struct sctp_sock *sp = sctp_sk(sk);
	struct sctp_endpoint *ep = sp->ep;
	struct crypto_shash *tfm = NULL;
	char alg[32];

	/* Allocate HMAC for generating cookie. */
	if (!sp->hmac && sp->sctp_hmac_alg) {
		sprintf(alg, "hmac(%s)", sp->sctp_hmac_alg);
		tfm = crypto_alloc_shash(alg, 0, 0);
		if (IS_ERR(tfm)) {
			net_info_ratelimited("failed to load transform for %s: %ld\n",
					     sp->sctp_hmac_alg, PTR_ERR(tfm));
			return -ENOSYS;
		}
		sctp_sk(sk)->hmac = tfm;
	}

	/*
	 * If a bind() or sctp_bindx() is not called prior to a listen()
	 * call that allows new associations to be accepted, the system
	 * picks an ephemeral port and will choose an address set equivalent
	 * to binding with a wildcard address.
	 *
	 * This is not currently spelled out in the SCTP sockets
	 * extensions draft, but follows the practice as seen in TCP
	 * sockets.
	 *
	 */
	inet_sk_set_state(sk, SCTP_SS_LISTENING);
	if (!ep->base.bind_addr.port) {
		if (sctp_autobind(sk))
			return -EAGAIN;
	} else {
		if (sctp_get_port(sk, inet_sk(sk)->inet_num)) {
			inet_sk_set_state(sk, SCTP_SS_CLOSED);
			return -EADDRINUSE;
		}
	}

	sk->sk_max_ack_backlog = backlog;
	return sctp_hash_endpoint(ep);
}
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
struct sock {int dummy; } ;
struct TYPE_3__ {struct sock* sk; int /*<<< orphan*/  bind_addr; int /*<<< orphan*/  inqueue; int /*<<< orphan*/  dead; } ;
struct sctp_endpoint {TYPE_1__ base; int /*<<< orphan*/  secret_key; int /*<<< orphan*/  endpoint_shared_keys; struct sctp_endpoint* digest; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ep; scalar_t__ bind_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_DEC (struct sctp_endpoint*) ; 
 int /*<<< orphan*/  WARN (int,char*,struct sctp_endpoint*) ; 
 int /*<<< orphan*/  kfree (struct sctp_endpoint*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sctp_auth_destroy_keys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_auth_free (struct sctp_endpoint*) ; 
 int /*<<< orphan*/  sctp_bind_addr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_inq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_put_port (struct sock*) ; 
 TYPE_2__* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sctp_endpoint_destroy(struct sctp_endpoint *ep)
{
	struct sock *sk;

	if (unlikely(!ep->base.dead)) {
		WARN(1, "Attempt to destroy undead endpoint %p!\n", ep);
		return;
	}

	/* Free the digest buffer */
	kfree(ep->digest);

	/* SCTP-AUTH: Free up AUTH releated data such as shared keys
	 * chunks and hmacs arrays that were allocated
	 */
	sctp_auth_destroy_keys(&ep->endpoint_shared_keys);
	sctp_auth_free(ep);

	/* Cleanup. */
	sctp_inq_free(&ep->base.inqueue);
	sctp_bind_addr_free(&ep->base.bind_addr);

	memset(ep->secret_key, 0, sizeof(ep->secret_key));

	sk = ep->base.sk;
	/* Remove and free the port */
	if (sctp_sk(sk)->bind_hash)
		sctp_put_port(sk);

	sctp_sk(sk)->ep = NULL;
	/* Give up our hold on the sock */
	sock_put(sk);

	kfree(ep);
	SCTP_DBG_OBJCNT_DEC(ep);
}
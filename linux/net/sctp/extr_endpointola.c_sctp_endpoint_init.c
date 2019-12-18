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
struct sock {int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; } ;
struct sctp_shared_key {int /*<<< orphan*/  key_list; } ;
struct TYPE_4__ {int dead; struct sock* sk; int /*<<< orphan*/  bind_addr; int /*<<< orphan*/  inqueue; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  type; } ;
struct sctp_endpoint {int /*<<< orphan*/  digest; TYPE_2__ base; int /*<<< orphan*/  ecn_enable; int /*<<< orphan*/  reconf_enable; int /*<<< orphan*/  prsctp_enable; int /*<<< orphan*/  endpoint_shared_keys; int /*<<< orphan*/  secret_key; int /*<<< orphan*/  rcvbuf_policy; int /*<<< orphan*/  sndbuf_policy; int /*<<< orphan*/  asocs; scalar_t__ asconf_enable; scalar_t__ auth_enable; } ;
struct TYPE_3__ {int /*<<< orphan*/  ecn_enable; int /*<<< orphan*/  reconf_enable; int /*<<< orphan*/  prsctp_enable; int /*<<< orphan*/  rcvbuf_policy; int /*<<< orphan*/  sndbuf_policy; scalar_t__ auth_enable; scalar_t__ addip_enable; } ;
struct net {TYPE_1__ sctp; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_CID_ASCONF ; 
 int /*<<< orphan*/  SCTP_CID_ASCONF_ACK ; 
 int /*<<< orphan*/  SCTP_EP_TYPE_SOCKET ; 
 int /*<<< orphan*/  SCTP_SIGNATURE_SIZE ; 
 int /*<<< orphan*/  SOCK_USE_WRITE_QUEUE ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sctp_auth_ep_add_chunkid (struct sctp_endpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_free (struct sctp_endpoint*) ; 
 scalar_t__ sctp_auth_init (struct sctp_endpoint*,int /*<<< orphan*/ ) ; 
 struct sctp_shared_key* sctp_auth_shkey_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_bind_addr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_data_ready ; 
 int /*<<< orphan*/  sctp_endpoint_bh_rcv ; 
 int /*<<< orphan*/  sctp_inq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_inq_set_th_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_write_space ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_endpoint *sctp_endpoint_init(struct sctp_endpoint *ep,
						struct sock *sk,
						gfp_t gfp)
{
	struct net *net = sock_net(sk);
	struct sctp_shared_key *null_key;

	ep->digest = kzalloc(SCTP_SIGNATURE_SIZE, gfp);
	if (!ep->digest)
		return NULL;

	ep->asconf_enable = net->sctp.addip_enable;
	ep->auth_enable = net->sctp.auth_enable;
	if (ep->auth_enable) {
		if (sctp_auth_init(ep, gfp))
			goto nomem;
		if (ep->asconf_enable) {
			sctp_auth_ep_add_chunkid(ep, SCTP_CID_ASCONF);
			sctp_auth_ep_add_chunkid(ep, SCTP_CID_ASCONF_ACK);
		}
	}

	/* Initialize the base structure. */
	/* What type of endpoint are we?  */
	ep->base.type = SCTP_EP_TYPE_SOCKET;

	/* Initialize the basic object fields. */
	refcount_set(&ep->base.refcnt, 1);
	ep->base.dead = false;

	/* Create an input queue.  */
	sctp_inq_init(&ep->base.inqueue);

	/* Set its top-half handler */
	sctp_inq_set_th_handler(&ep->base.inqueue, sctp_endpoint_bh_rcv);

	/* Initialize the bind addr area */
	sctp_bind_addr_init(&ep->base.bind_addr, 0);

	/* Create the lists of associations.  */
	INIT_LIST_HEAD(&ep->asocs);

	/* Use SCTP specific send buffer space queues.  */
	ep->sndbuf_policy = net->sctp.sndbuf_policy;

	sk->sk_data_ready = sctp_data_ready;
	sk->sk_write_space = sctp_write_space;
	sock_set_flag(sk, SOCK_USE_WRITE_QUEUE);

	/* Get the receive buffer policy for this endpoint */
	ep->rcvbuf_policy = net->sctp.rcvbuf_policy;

	/* Initialize the secret key used with cookie. */
	get_random_bytes(ep->secret_key, sizeof(ep->secret_key));

	/* SCTP-AUTH extensions*/
	INIT_LIST_HEAD(&ep->endpoint_shared_keys);
	null_key = sctp_auth_shkey_create(0, gfp);
	if (!null_key)
		goto nomem_shkey;

	list_add(&null_key->key_list, &ep->endpoint_shared_keys);

	/* Add the null key to the endpoint shared keys list and
	 * set the hmcas and chunks pointers.
	 */
	ep->prsctp_enable = net->sctp.prsctp_enable;
	ep->reconf_enable = net->sctp.reconf_enable;
	ep->ecn_enable = net->sctp.ecn_enable;

	/* Remember who we are attached to.  */
	ep->base.sk = sk;
	sock_hold(ep->base.sk);

	return ep;

nomem_shkey:
	sctp_auth_free(ep);
nomem:
	kfree(ep->digest);
	return NULL;

}
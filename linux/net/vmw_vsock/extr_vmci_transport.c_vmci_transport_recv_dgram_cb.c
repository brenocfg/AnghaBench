#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vsock_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;
struct vmci_datagram {TYPE_1__ src; } ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t VMCI_DG_SIZE (struct vmci_datagram*) ; 
 int VMCI_ERROR_NO_ACCESS ; 
 int VMCI_ERROR_NO_MEM ; 
 int VMCI_SUCCESS ; 
 struct sk_buff* alloc_skb (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct vmci_datagram*,size_t) ; 
 int /*<<< orphan*/  sk_receive_skb (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  vmci_transport_allow_dgram (struct vsock_sock*,int /*<<< orphan*/ ) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int vmci_transport_recv_dgram_cb(void *data, struct vmci_datagram *dg)
{
	struct sock *sk;
	size_t size;
	struct sk_buff *skb;
	struct vsock_sock *vsk;

	sk = (struct sock *)data;

	/* This handler is privileged when this module is running on the host.
	 * We will get datagrams from all endpoints (even VMs that are in a
	 * restricted context). If we get one from a restricted context then
	 * the destination socket must be trusted.
	 *
	 * NOTE: We access the socket struct without holding the lock here.
	 * This is ok because the field we are interested is never modified
	 * outside of the create and destruct socket functions.
	 */
	vsk = vsock_sk(sk);
	if (!vmci_transport_allow_dgram(vsk, dg->src.context))
		return VMCI_ERROR_NO_ACCESS;

	size = VMCI_DG_SIZE(dg);

	/* Attach the packet to the socket's receive queue as an sk_buff. */
	skb = alloc_skb(size, GFP_ATOMIC);
	if (!skb)
		return VMCI_ERROR_NO_MEM;

	/* sk_receive_skb() will do a sock_put(), so hold here. */
	sock_hold(sk);
	skb_put(skb, size);
	memcpy(skb->data, dg, size);
	sk_receive_skb(sk, skb, 0);

	return VMCI_SUCCESS;
}
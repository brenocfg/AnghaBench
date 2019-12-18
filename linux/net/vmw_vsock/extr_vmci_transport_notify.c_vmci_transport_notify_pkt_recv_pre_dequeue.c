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
struct vmci_transport_recv_notify_data {int /*<<< orphan*/  consume_head; int /*<<< orphan*/  produce_tail; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qpair; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmci_qpair_get_consume_indexes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int
vmci_transport_notify_pkt_recv_pre_dequeue(
				struct sock *sk,
				size_t target,
				struct vmci_transport_recv_notify_data *data)
{
	struct vsock_sock *vsk = vsock_sk(sk);

	/* Now consume up to len bytes from the queue.  Note that since we have
	 * the socket locked we should copy at least ready bytes.
	 */
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	vmci_qpair_get_consume_indexes(vmci_trans(vsk)->qpair,
				       &data->produce_tail,
				       &data->consume_head);
#endif

	return 0;
}
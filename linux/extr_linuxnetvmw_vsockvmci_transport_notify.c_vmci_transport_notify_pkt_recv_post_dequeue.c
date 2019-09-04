#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vsock_sock {int dummy; } ;
struct vmci_transport_recv_notify_data {int dummy; } ;
struct sock {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int vmci_transport_send_read_notification (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int
vmci_transport_notify_pkt_recv_post_dequeue(
				struct sock *sk,
				size_t target,
				ssize_t copied,
				bool data_read,
				struct vmci_transport_recv_notify_data *data)
{
	struct vsock_sock *vsk;
	int err;

	vsk = vsock_sk(sk);
	err = 0;

	if (data_read) {
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
		/* Detect a wrap-around to maintain queue generation.  Note
		 * that this is safe since we hold the socket lock across the
		 * two queue pair operations.
		 */
		if (copied >=
			vmci_trans(vsk)->consume_size - data->consume_head)
			PKT_FIELD(vsk, consume_q_generation)++;
#endif

		err = vmci_transport_send_read_notification(sk);
		if (err < 0)
			return err;

	}
	return err;
}
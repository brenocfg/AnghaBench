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
struct vsock_sock {int sent_request; int ignore_connecting_rst; } ;
struct vmci_transport_packet {int dummy; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_pair_size; } ;

/* Variables and functions */
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 
 int vmci_transport_error_to_vsock_error (int) ; 
 int vmci_transport_send_conn_request (struct sock*,int /*<<< orphan*/ ) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int
vmci_transport_recv_connecting_client_invalid(struct sock *sk,
					      struct vmci_transport_packet *pkt)
{
	int err = 0;
	struct vsock_sock *vsk = vsock_sk(sk);

	if (vsk->sent_request) {
		vsk->sent_request = false;
		vsk->ignore_connecting_rst = true;

		err = vmci_transport_send_conn_request(
			sk, vmci_trans(vsk)->queue_pair_size);
		if (err < 0)
			err = vmci_transport_error_to_vsock_error(err);
		else
			err = 0;

	}

	return err;
}
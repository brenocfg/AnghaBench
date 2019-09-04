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
struct sock {void* sk_state; } ;
struct vsock_sock {int sent_request; struct sock sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_pair_size; } ;

/* Variables and functions */
 void* TCP_CLOSE ; 
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 
 int vmci_transport_new_proto_supported_versions () ; 
 scalar_t__ vmci_transport_old_proto_override (int*) ; 
 int vmci_transport_send_conn_request (struct sock*,int /*<<< orphan*/ ) ; 
 int vmci_transport_send_conn_request2 (struct sock*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vmci_transport_connect(struct vsock_sock *vsk)
{
	int err;
	bool old_pkt_proto = false;
	struct sock *sk = &vsk->sk;

	if (vmci_transport_old_proto_override(&old_pkt_proto) &&
		old_pkt_proto) {
		err = vmci_transport_send_conn_request(
			sk, vmci_trans(vsk)->queue_pair_size);
		if (err < 0) {
			sk->sk_state = TCP_CLOSE;
			return err;
		}
	} else {
		int supported_proto_versions =
			vmci_transport_new_proto_supported_versions();
		err = vmci_transport_send_conn_request2(
				sk, vmci_trans(vsk)->queue_pair_size,
				supported_proto_versions);
		if (err < 0) {
			sk->sk_state = TCP_CLOSE;
			return err;
		}

		vsk->sent_request = true;
	}

	return err;
}
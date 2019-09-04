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
struct vsock_sock {int peer_shutdown; } ;
struct vmci_transport_send_notify_data {int dummy; } ;
struct sock {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  qpair; } ;

/* Variables and functions */
 int RCV_SHUTDOWN ; 
 int VMCI_TRANSPORT_MAX_DGRAM_RESENDS ; 
 int /*<<< orphan*/  pr_err (char*,struct sock*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ vmci_qpair_produce_buf_ready (int /*<<< orphan*/ ) ; 
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 
 int vmci_transport_send_wrote (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int
vmci_transport_notify_pkt_send_post_enqueue(
				struct sock *sk,
				ssize_t written,
				struct vmci_transport_send_notify_data *data)
{
	int err = 0;
	struct vsock_sock *vsk;
	bool sent_wrote = false;
	bool was_empty;
	int retries = 0;

	vsk = vsock_sk(sk);

	smp_mb();

	was_empty =
		vmci_qpair_produce_buf_ready(vmci_trans(vsk)->qpair) == written;
	if (was_empty) {
		while (!(vsk->peer_shutdown & RCV_SHUTDOWN) &&
		       !sent_wrote &&
		       retries < VMCI_TRANSPORT_MAX_DGRAM_RESENDS) {
			err = vmci_transport_send_wrote(sk);
			if (err >= 0)
				sent_wrote = true;

			retries++;
		}
	}

	if (retries >= VMCI_TRANSPORT_MAX_DGRAM_RESENDS && !sent_wrote) {
		pr_err("%p unable to send wrote notification to peer\n",
		       sk);
		return err;
	}

	return err;
}
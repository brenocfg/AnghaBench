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
struct vmci_transport_packet {int dummy; } ;
struct sockaddr_vm {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
vmci_transport_handle_waiting_read(struct sock *sk,
				   struct vmci_transport_packet *pkt,
				   bool bottom_half,
				   struct sockaddr_vm *dst,
				   struct sockaddr_vm *src)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	struct vsock_sock *vsk;

	vsk = vsock_sk(sk);

	PKT_FIELD(vsk, peer_waiting_read) = true;
	memcpy(&PKT_FIELD(vsk, peer_waiting_read_info), &pkt->u.wait,
	       sizeof(PKT_FIELD(vsk, peer_waiting_read_info)));

	if (vmci_transport_notify_waiting_read(vsk)) {
		bool sent;

		if (bottom_half)
			sent = vmci_transport_send_wrote_bh(dst, src) > 0;
		else
			sent = vmci_transport_send_wrote(sk) > 0;

		if (sent)
			PKT_FIELD(vsk, peer_waiting_read) = false;
	}
#endif
}
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
struct vmci_transport_packet {int type; } ;
struct sockaddr_vm {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
#define  VMCI_TRANSPORT_PACKET_TYPE_READ 129 
#define  VMCI_TRANSPORT_PACKET_TYPE_WROTE 128 
 int /*<<< orphan*/  vmci_transport_handle_read (struct sock*,struct vmci_transport_packet*,int,struct sockaddr_vm*,struct sockaddr_vm*) ; 
 int /*<<< orphan*/  vmci_transport_handle_wrote (struct sock*,struct vmci_transport_packet*,int,struct sockaddr_vm*,struct sockaddr_vm*) ; 

__attribute__((used)) static void
vmci_transport_notify_pkt_handle_pkt(
				struct sock *sk,
				struct vmci_transport_packet *pkt,
				bool bottom_half,
				struct sockaddr_vm *dst,
				struct sockaddr_vm *src, bool *pkt_processed)
{
	bool processed = false;

	switch (pkt->type) {
	case VMCI_TRANSPORT_PACKET_TYPE_WROTE:
		vmci_transport_handle_wrote(sk, pkt, bottom_half, dst, src);
		processed = true;
		break;
	case VMCI_TRANSPORT_PACKET_TYPE_READ:
		vmci_transport_handle_read(sk, pkt, bottom_half, dst, src);
		processed = true;
		break;
	}

	if (pkt_processed)
		*pkt_processed = processed;
}
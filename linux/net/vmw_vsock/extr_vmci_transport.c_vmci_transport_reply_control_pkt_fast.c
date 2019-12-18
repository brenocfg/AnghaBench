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
typedef  int /*<<< orphan*/  u64 ;
struct vmci_transport_waiting_info {int dummy; } ;
struct vmci_transport_packet {scalar_t__ type; } ;
struct vmci_handle {int dummy; } ;
struct sockaddr_vm {int dummy; } ;
typedef  enum vmci_transport_packet_type { ____Placeholder_vmci_transport_packet_type } vmci_transport_packet_type ;

/* Variables and functions */
 scalar_t__ VMCI_TRANSPORT_PACKET_TYPE_RST ; 
 int /*<<< orphan*/  VSOCK_PROTO_INVALID ; 
 int __vmci_transport_send_control_pkt (struct vmci_transport_packet*,struct sockaddr_vm*,struct sockaddr_vm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmci_transport_waiting_info*,int /*<<< orphan*/ ,struct vmci_handle,int) ; 
 int /*<<< orphan*/  vmci_transport_packet_get_addresses (struct vmci_transport_packet*,struct sockaddr_vm*,struct sockaddr_vm*) ; 

__attribute__((used)) static int
vmci_transport_reply_control_pkt_fast(struct vmci_transport_packet *pkt,
				      enum vmci_transport_packet_type type,
				      u64 size,
				      u64 mode,
				      struct vmci_transport_waiting_info *wait,
				      struct vmci_handle handle)
{
	struct vmci_transport_packet reply;
	struct sockaddr_vm src, dst;

	if (pkt->type == VMCI_TRANSPORT_PACKET_TYPE_RST) {
		return 0;
	} else {
		vmci_transport_packet_get_addresses(pkt, &src, &dst);
		return __vmci_transport_send_control_pkt(&reply, &src, &dst,
							 type,
							 size, mode, wait,
							 VSOCK_PROTO_INVALID,
							 handle, true);
	}
}
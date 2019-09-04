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
struct vmci_transport_packet {int dummy; } ;
struct vmci_handle {int dummy; } ;
struct sockaddr_vm {int dummy; } ;
typedef  enum vmci_transport_packet_type { ____Placeholder_vmci_transport_packet_type } vmci_transport_packet_type ;

/* Variables and functions */
 int /*<<< orphan*/  VSOCK_PROTO_INVALID ; 
 int __vmci_transport_send_control_pkt (struct vmci_transport_packet*,struct sockaddr_vm*,struct sockaddr_vm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmci_transport_waiting_info*,int /*<<< orphan*/ ,struct vmci_handle,int) ; 

__attribute__((used)) static int
vmci_transport_send_control_pkt_bh(struct sockaddr_vm *src,
				   struct sockaddr_vm *dst,
				   enum vmci_transport_packet_type type,
				   u64 size,
				   u64 mode,
				   struct vmci_transport_waiting_info *wait,
				   struct vmci_handle handle)
{
	/* Note that it is safe to use a single packet across all CPUs since
	 * two tasklets of the same type are guaranteed to not ever run
	 * simultaneously. If that ever changes, or VMCI stops using tasklets,
	 * we can use per-cpu packets.
	 */
	static struct vmci_transport_packet pkt;

	return __vmci_transport_send_control_pkt(&pkt, src, dst, type,
						 size, mode, wait,
						 VSOCK_PROTO_INVALID, handle,
						 false);
}
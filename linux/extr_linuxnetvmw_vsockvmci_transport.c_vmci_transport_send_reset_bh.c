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
struct vmci_transport_packet {scalar_t__ type; } ;
struct sockaddr_vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_INVALID_HANDLE ; 
 scalar_t__ VMCI_TRANSPORT_PACKET_TYPE_RST ; 
 int vmci_transport_send_control_pkt_bh (struct sockaddr_vm*,struct sockaddr_vm*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmci_transport_send_reset_bh(struct sockaddr_vm *dst,
					struct sockaddr_vm *src,
					struct vmci_transport_packet *pkt)
{
	if (pkt->type == VMCI_TRANSPORT_PACKET_TYPE_RST)
		return 0;
	return vmci_transport_send_control_pkt_bh(
					dst, src,
					VMCI_TRANSPORT_PACKET_TYPE_RST, 0,
					0, NULL, VMCI_INVALID_HANDLE);
}
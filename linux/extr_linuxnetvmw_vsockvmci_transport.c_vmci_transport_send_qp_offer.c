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
struct vmci_handle {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_TRANSPORT_PACKET_TYPE_OFFER ; 
 int /*<<< orphan*/  VSOCK_PROTO_INVALID ; 
 int vmci_transport_send_control_pkt (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vmci_handle) ; 

__attribute__((used)) static int vmci_transport_send_qp_offer(struct sock *sk,
					struct vmci_handle handle)
{
	return vmci_transport_send_control_pkt(
					sk, VMCI_TRANSPORT_PACKET_TYPE_OFFER, 0,
					0, NULL,
					VSOCK_PROTO_INVALID, handle);
}
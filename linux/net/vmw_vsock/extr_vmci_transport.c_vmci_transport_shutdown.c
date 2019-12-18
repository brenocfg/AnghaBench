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
struct vsock_sock {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  VMCI_TRANSPORT_PACKET_TYPE_SHUTDOWN ; 
 int /*<<< orphan*/  VSOCK_PROTO_INVALID ; 
 int vmci_transport_send_control_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmci_transport_shutdown(struct vsock_sock *vsk, int mode)
{
	return vmci_transport_send_control_pkt(
					&vsk->sk,
					VMCI_TRANSPORT_PACKET_TYPE_SHUTDOWN,
					0, mode, NULL,
					VSOCK_PROTO_INVALID,
					VMCI_INVALID_HANDLE);
}
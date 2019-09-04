#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_vm {int dummy; } ;
struct vsock_sock {struct sockaddr_vm local_addr; struct sockaddr_vm remote_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;
struct TYPE_4__ {TYPE_1__ src; } ;
struct vmci_transport_packet {scalar_t__ type; int /*<<< orphan*/  src_port; TYPE_2__ dg; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VMCI_INVALID_HANDLE ; 
 scalar_t__ VMCI_TRANSPORT_PACKET_TYPE_RST ; 
 int /*<<< orphan*/  VSOCK_PROTO_INVALID ; 
 int vmci_transport_alloc_send_control_pkt (struct sockaddr_vm*,struct sockaddr_vm*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vsock_addr_bound (struct sockaddr_vm*) ; 
 int /*<<< orphan*/  vsock_addr_init (struct sockaddr_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int vmci_transport_send_reset(struct sock *sk,
				     struct vmci_transport_packet *pkt)
{
	struct sockaddr_vm *dst_ptr;
	struct sockaddr_vm dst;
	struct vsock_sock *vsk;

	if (pkt->type == VMCI_TRANSPORT_PACKET_TYPE_RST)
		return 0;

	vsk = vsock_sk(sk);

	if (!vsock_addr_bound(&vsk->local_addr))
		return -EINVAL;

	if (vsock_addr_bound(&vsk->remote_addr)) {
		dst_ptr = &vsk->remote_addr;
	} else {
		vsock_addr_init(&dst, pkt->dg.src.context,
				pkt->src_port);
		dst_ptr = &dst;
	}
	return vmci_transport_alloc_send_control_pkt(&vsk->local_addr, dst_ptr,
					     VMCI_TRANSPORT_PACKET_TYPE_RST,
					     0, 0, NULL, VSOCK_PROTO_INVALID,
					     VMCI_INVALID_HANDLE);
}
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
typedef  scalar_t__ u32 ;
struct vsock_sock {int /*<<< orphan*/  local_addr; int /*<<< orphan*/  sk; } ;
struct sockaddr_vm {scalar_t__ svm_port; scalar_t__ svm_cid; } ;
struct TYPE_3__ {int /*<<< orphan*/  resource; } ;
struct TYPE_4__ {TYPE_1__ dg_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_BIND_SERVICE ; 
 int EACCES ; 
 scalar_t__ LAST_RESERVED_PORT ; 
 scalar_t__ VMADDR_CID_ANY ; 
 scalar_t__ VMADDR_PORT_ANY ; 
 scalar_t__ VMCI_FLAG_ANYCID_DG_HND ; 
 scalar_t__ VMCI_INVALID_ID ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_2__* vmci_trans (struct vsock_sock*) ; 
 int vmci_transport_datagram_create_hnd (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int vmci_transport_error_to_vsock_error (int) ; 
 int /*<<< orphan*/  vmci_transport_recv_dgram_cb ; 
 int /*<<< orphan*/  vsock_addr_init (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmci_transport_dgram_bind(struct vsock_sock *vsk,
				     struct sockaddr_vm *addr)
{
	u32 port;
	u32 flags;
	int err;

	/* VMCI will select a resource ID for us if we provide
	 * VMCI_INVALID_ID.
	 */
	port = addr->svm_port == VMADDR_PORT_ANY ?
			VMCI_INVALID_ID : addr->svm_port;

	if (port <= LAST_RESERVED_PORT && !capable(CAP_NET_BIND_SERVICE))
		return -EACCES;

	flags = addr->svm_cid == VMADDR_CID_ANY ?
				VMCI_FLAG_ANYCID_DG_HND : 0;

	err = vmci_transport_datagram_create_hnd(port, flags,
						 vmci_transport_recv_dgram_cb,
						 &vsk->sk,
						 &vmci_trans(vsk)->dg_handle);
	if (err < VMCI_SUCCESS)
		return vmci_transport_error_to_vsock_error(err);
	vsock_addr_init(&vsk->local_addr, addr->svm_cid,
			vmci_trans(vsk)->dg_handle.resource);

	return 0;
}
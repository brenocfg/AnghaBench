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
struct TYPE_2__ {int /*<<< orphan*/  svm_port; int /*<<< orphan*/  svm_cid; } ;
struct vsock_sock {TYPE_1__ local_addr; } ;
struct vmci_datagram {size_t payload_size; void* src; void* dst; } ;
struct sockaddr_vm {int /*<<< orphan*/  svm_port; int /*<<< orphan*/  svm_cid; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VMCI_DG_PAYLOAD (struct vmci_datagram*) ; 
 size_t VMCI_MAX_DG_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  kfree (struct vmci_datagram*) ; 
 struct vmci_datagram* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_from_msg (int /*<<< orphan*/ ,struct msghdr*,size_t) ; 
 int vmci_datagram_send (struct vmci_datagram*) ; 
 void* vmci_make_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_transport_allow_dgram (struct vsock_sock*,int /*<<< orphan*/ ) ; 
 int vmci_transport_error_to_vsock_error (int) ; 

__attribute__((used)) static int vmci_transport_dgram_enqueue(
	struct vsock_sock *vsk,
	struct sockaddr_vm *remote_addr,
	struct msghdr *msg,
	size_t len)
{
	int err;
	struct vmci_datagram *dg;

	if (len > VMCI_MAX_DG_PAYLOAD_SIZE)
		return -EMSGSIZE;

	if (!vmci_transport_allow_dgram(vsk, remote_addr->svm_cid))
		return -EPERM;

	/* Allocate a buffer for the user's message and our packet header. */
	dg = kmalloc(len + sizeof(*dg), GFP_KERNEL);
	if (!dg)
		return -ENOMEM;

	memcpy_from_msg(VMCI_DG_PAYLOAD(dg), msg, len);

	dg->dst = vmci_make_handle(remote_addr->svm_cid,
				   remote_addr->svm_port);
	dg->src = vmci_make_handle(vsk->local_addr.svm_cid,
				   vsk->local_addr.svm_port);
	dg->payload_size = len;

	err = vmci_datagram_send(dg);
	kfree(dg);
	if (err < 0)
		return vmci_transport_error_to_vsock_error(err);

	return err - sizeof(*dg);
}
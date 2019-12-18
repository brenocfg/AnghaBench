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
struct vsock_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dg_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  vmci_datagram_destroy_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_handle_is_invalid (int /*<<< orphan*/ ) ; 
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 
 int /*<<< orphan*/  vsock_remove_sock (struct vsock_sock*) ; 

__attribute__((used)) static void vmci_transport_release(struct vsock_sock *vsk)
{
	vsock_remove_sock(vsk);

	if (!vmci_handle_is_invalid(vmci_trans(vsk)->dg_handle)) {
		vmci_datagram_destroy_handle(vmci_trans(vsk)->dg_handle);
		vmci_trans(vsk)->dg_handle = VMCI_INVALID_HANDLE;
	}
}
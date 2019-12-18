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
struct vsock_sock {int /*<<< orphan*/ * trans; } ;
struct TYPE_4__ {int /*<<< orphan*/  elem; TYPE_1__* notify_ops; int /*<<< orphan*/  lock; int /*<<< orphan*/ * sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* socket_destruct ) (struct vsock_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vsock_sock*) ; 
 TYPE_2__* vmci_trans (struct vsock_sock*) ; 
 int /*<<< orphan*/  vmci_transport_cleanup_list ; 
 int /*<<< orphan*/  vmci_transport_cleanup_lock ; 
 int /*<<< orphan*/  vmci_transport_cleanup_work ; 

__attribute__((used)) static void vmci_transport_destruct(struct vsock_sock *vsk)
{
	/* transport can be NULL if we hit a failure at init() time */
	if (!vmci_trans(vsk))
		return;

	/* Ensure that the detach callback doesn't use the sk/vsk
	 * we are about to destruct.
	 */
	spin_lock_bh(&vmci_trans(vsk)->lock);
	vmci_trans(vsk)->sk = NULL;
	spin_unlock_bh(&vmci_trans(vsk)->lock);

	if (vmci_trans(vsk)->notify_ops)
		vmci_trans(vsk)->notify_ops->socket_destruct(vsk);

	spin_lock_bh(&vmci_transport_cleanup_lock);
	list_add(&vmci_trans(vsk)->elem, &vmci_transport_cleanup_list);
	spin_unlock_bh(&vmci_transport_cleanup_lock);
	schedule_work(&vmci_transport_cleanup_work);

	vsk->trans = NULL;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct vmci_transport {int /*<<< orphan*/  lock; int /*<<< orphan*/  sk; int /*<<< orphan*/  qp_handle; } ;
struct vmci_event_payload_qp {int /*<<< orphan*/  handle; } ;
struct vmci_event_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bh_lock_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_unlock_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct vmci_event_payload_qp* vmci_event_data_const_payload (struct vmci_event_data const*) ; 
 int /*<<< orphan*/  vmci_handle_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vmci_handle_is_invalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_transport_handle_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmci_transport_peer_detach_cb(u32 sub_id,
					  const struct vmci_event_data *e_data,
					  void *client_data)
{
	struct vmci_transport *trans = client_data;
	const struct vmci_event_payload_qp *e_payload;

	e_payload = vmci_event_data_const_payload(e_data);

	/* XXX This is lame, we should provide a way to lookup sockets by
	 * qp_handle.
	 */
	if (vmci_handle_is_invalid(e_payload->handle) ||
	    !vmci_handle_is_equal(trans->qp_handle, e_payload->handle))
		return;

	/* We don't ask for delayed CBs when we subscribe to this event (we
	 * pass 0 as flags to vmci_event_subscribe()).  VMCI makes no
	 * guarantees in that case about what context we might be running in,
	 * so it could be BH or process, blockable or non-blockable.  So we
	 * need to account for all possible contexts here.
	 */
	spin_lock_bh(&trans->lock);
	if (!trans->sk)
		goto out;

	/* Apart from here, trans->lock is only grabbed as part of sk destruct,
	 * where trans->sk isn't locked.
	 */
	bh_lock_sock(trans->sk);

	vmci_transport_handle_detach(trans->sk);

	bh_unlock_sock(trans->sk);
 out:
	spin_unlock_bh(&trans->lock);
}
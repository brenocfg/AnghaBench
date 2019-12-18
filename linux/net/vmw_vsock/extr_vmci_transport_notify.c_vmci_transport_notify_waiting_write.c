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
typedef  scalar_t__ u64 ;
struct vsock_sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ consume_size; int /*<<< orphan*/  qpair; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int PKT_FIELD (struct vsock_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peer_waiting_write ; 
 int /*<<< orphan*/  peer_waiting_write_detected ; 
 scalar_t__ vmci_qpair_consume_free_space (int /*<<< orphan*/ ) ; 
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 
 int /*<<< orphan*/  write_notify_min_window ; 
 int /*<<< orphan*/  write_notify_window ; 

__attribute__((used)) static bool vmci_transport_notify_waiting_write(struct vsock_sock *vsk)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	bool retval;
	u64 notify_limit;

	if (!PKT_FIELD(vsk, peer_waiting_write))
		return false;

#ifdef VSOCK_OPTIMIZATION_FLOW_CONTROL
	/* When the sender blocks, we take that as a sign that the sender is
	 * faster than the receiver. To reduce the transmit rate of the sender,
	 * we delay the sending of the read notification by decreasing the
	 * write_notify_window. The notification is delayed until the number of
	 * bytes used in the queue drops below the write_notify_window.
	 */

	if (!PKT_FIELD(vsk, peer_waiting_write_detected)) {
		PKT_FIELD(vsk, peer_waiting_write_detected) = true;
		if (PKT_FIELD(vsk, write_notify_window) < PAGE_SIZE) {
			PKT_FIELD(vsk, write_notify_window) =
			    PKT_FIELD(vsk, write_notify_min_window);
		} else {
			PKT_FIELD(vsk, write_notify_window) -= PAGE_SIZE;
			if (PKT_FIELD(vsk, write_notify_window) <
			    PKT_FIELD(vsk, write_notify_min_window))
				PKT_FIELD(vsk, write_notify_window) =
				    PKT_FIELD(vsk, write_notify_min_window);

		}
	}
	notify_limit = vmci_trans(vsk)->consume_size -
		PKT_FIELD(vsk, write_notify_window);
#else
	notify_limit = 0;
#endif

	/* For now we ignore the wait information and just see if the free
	 * space exceeds the notify limit.  Note that improving this function
	 * to be more intelligent will not require a protocol change and will
	 * retain compatibility between endpoints with mixed versions of this
	 * function.
	 *
	 * The notify_limit is used to delay notifications in the case where
	 * flow control is enabled. Below the test is expressed in terms of
	 * free space in the queue: if free_space > ConsumeSize -
	 * write_notify_window then notify An alternate way of expressing this
	 * is to rewrite the expression to use the data ready in the receive
	 * queue: if write_notify_window > bufferReady then notify as
	 * free_space == ConsumeSize - bufferReady.
	 */
	retval = vmci_qpair_consume_free_space(vmci_trans(vsk)->qpair) >
		notify_limit;
#ifdef VSOCK_OPTIMIZATION_FLOW_CONTROL
	if (retval) {
		/*
		 * Once we notify the peer, we reset the detected flag so the
		 * next wait will again cause a decrease in the window size.
		 */

		PKT_FIELD(vsk, peer_waiting_write_detected) = false;
	}
#endif
	return retval;
#else
	return true;
#endif
}
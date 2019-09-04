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
typedef  int /*<<< orphan*/  u64 ;
struct sock {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool send_waiting_read(struct sock *sk, u64 room_needed)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	struct vsock_sock *vsk;
	struct vmci_transport_waiting_info waiting_info;
	u64 tail;
	u64 head;
	u64 room_left;
	bool ret;

	vsk = vsock_sk(sk);

	if (PKT_FIELD(vsk, sent_waiting_read))
		return true;

	if (PKT_FIELD(vsk, write_notify_window) <
			vmci_trans(vsk)->consume_size)
		PKT_FIELD(vsk, write_notify_window) =
		    min(PKT_FIELD(vsk, write_notify_window) + PAGE_SIZE,
			vmci_trans(vsk)->consume_size);

	vmci_qpair_get_consume_indexes(vmci_trans(vsk)->qpair, &tail, &head);
	room_left = vmci_trans(vsk)->consume_size - head;
	if (room_needed >= room_left) {
		waiting_info.offset = room_needed - room_left;
		waiting_info.generation =
		    PKT_FIELD(vsk, consume_q_generation) + 1;
	} else {
		waiting_info.offset = head + room_needed;
		waiting_info.generation = PKT_FIELD(vsk, consume_q_generation);
	}

	ret = vmci_transport_send_waiting_read(sk, &waiting_info) > 0;
	if (ret)
		PKT_FIELD(vsk, sent_waiting_read) = true;

	return ret;
#else
	return true;
#endif
}
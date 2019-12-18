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
struct vmci_transport_waiting_info {int generation; scalar_t__ offset; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ produce_size; int /*<<< orphan*/  qpair; } ;

/* Variables and functions */
 int PKT_FIELD (struct vsock_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  produce_q_generation ; 
 int /*<<< orphan*/  sent_waiting_write ; 
 int /*<<< orphan*/  vmci_qpair_get_produce_indexes (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 
 scalar_t__ vmci_transport_send_waiting_write (struct sock*,struct vmci_transport_waiting_info*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static bool send_waiting_write(struct sock *sk, u64 room_needed)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	struct vsock_sock *vsk;
	struct vmci_transport_waiting_info waiting_info;
	u64 tail;
	u64 head;
	u64 room_left;
	bool ret;

	vsk = vsock_sk(sk);

	if (PKT_FIELD(vsk, sent_waiting_write))
		return true;

	vmci_qpair_get_produce_indexes(vmci_trans(vsk)->qpair, &tail, &head);
	room_left = vmci_trans(vsk)->produce_size - tail;
	if (room_needed + 1 >= room_left) {
		/* Wraps around to current generation. */
		waiting_info.offset = room_needed + 1 - room_left;
		waiting_info.generation = PKT_FIELD(vsk, produce_q_generation);
	} else {
		waiting_info.offset = tail + room_needed + 1;
		waiting_info.generation =
		    PKT_FIELD(vsk, produce_q_generation) - 1;
	}

	ret = vmci_transport_send_waiting_write(sk, &waiting_info) > 0;
	if (ret)
		PKT_FIELD(vsk, sent_waiting_write) = true;

	return ret;
#else
	return true;
#endif
}
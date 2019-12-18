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
struct vsock_sock {int dummy; } ;
struct vmci_transport_recv_notify_data {int notify_on_block; scalar_t__ produce_tail; scalar_t__ consume_head; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 size_t PKT_FIELD (struct vsock_sock*,int /*<<< orphan*/ ) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 
 int /*<<< orphan*/  write_notify_min_window ; 
 int /*<<< orphan*/  write_notify_window ; 

__attribute__((used)) static int
vmci_transport_notify_pkt_recv_init(
			struct sock *sk,
			size_t target,
			struct vmci_transport_recv_notify_data *data)
{
	struct vsock_sock *vsk = vsock_sk(sk);

#ifdef VSOCK_OPTIMIZATION_WAITING_NOTIFY
	data->consume_head = 0;
	data->produce_tail = 0;
#ifdef VSOCK_OPTIMIZATION_FLOW_CONTROL
	data->notify_on_block = false;

	if (PKT_FIELD(vsk, write_notify_min_window) < target + 1) {
		PKT_FIELD(vsk, write_notify_min_window) = target + 1;
		if (PKT_FIELD(vsk, write_notify_window) <
		    PKT_FIELD(vsk, write_notify_min_window)) {
			/* If the current window is smaller than the new
			 * minimal window size, we need to reevaluate whether
			 * we need to notify the sender. If the number of ready
			 * bytes are smaller than the new window, we need to
			 * send a notification to the sender before we block.
			 */

			PKT_FIELD(vsk, write_notify_window) =
			    PKT_FIELD(vsk, write_notify_min_window);
			data->notify_on_block = true;
		}
	}
#endif
#endif

	return 0;
}
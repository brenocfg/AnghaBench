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
struct vmci_transport_recv_notify_data {int notify_on_block; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int vmci_transport_send_read_notification (struct sock*) ; 
 int /*<<< orphan*/  vsock_block_update_write_window (struct sock*) ; 

__attribute__((used)) static int
vmci_transport_notify_pkt_recv_pre_block(
				struct sock *sk,
				size_t target,
				struct vmci_transport_recv_notify_data *data)
{
	int err = 0;

	vsock_block_update_write_window(sk);

	if (data->notify_on_block) {
		err = vmci_transport_send_read_notification(sk);
		if (err < 0)
			return err;
		data->notify_on_block = false;
	}

	return err;
}
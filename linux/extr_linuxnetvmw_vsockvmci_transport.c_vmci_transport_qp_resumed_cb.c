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
struct vmci_event_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmci_transport_handle_detach ; 
 int /*<<< orphan*/  vsock_for_each_connected_socket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmci_transport_qp_resumed_cb(u32 sub_id,
					 const struct vmci_event_data *e_data,
					 void *client_data)
{
	vsock_for_each_connected_socket(vmci_transport_handle_detach);
}
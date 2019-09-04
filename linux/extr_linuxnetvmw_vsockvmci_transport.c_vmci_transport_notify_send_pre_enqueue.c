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
struct vsock_transport_send_notify_data {int dummy; } ;
struct vsock_sock {int /*<<< orphan*/  sk; } ;
struct vmci_transport_send_notify_data {int dummy; } ;
struct TYPE_4__ {TYPE_1__* notify_ops; } ;
struct TYPE_3__ {int (* send_pre_enqueue ) (int /*<<< orphan*/ *,struct vmci_transport_send_notify_data*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct vmci_transport_send_notify_data*) ; 
 TYPE_2__* vmci_trans (struct vsock_sock*) ; 

__attribute__((used)) static int vmci_transport_notify_send_pre_enqueue(
	struct vsock_sock *vsk,
	struct vsock_transport_send_notify_data *data)
{
	return vmci_trans(vsk)->notify_ops->send_pre_enqueue(
			&vsk->sk,
			(struct vmci_transport_send_notify_data *)data);
}
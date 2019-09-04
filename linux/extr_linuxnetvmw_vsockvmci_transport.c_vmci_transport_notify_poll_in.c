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
struct vsock_sock {int /*<<< orphan*/  sk; } ;
struct TYPE_4__ {TYPE_1__* notify_ops; } ;
struct TYPE_3__ {int (* poll_in ) (int /*<<< orphan*/ *,size_t,int*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,size_t,int*) ; 
 TYPE_2__* vmci_trans (struct vsock_sock*) ; 

__attribute__((used)) static int vmci_transport_notify_poll_in(
	struct vsock_sock *vsk,
	size_t target,
	bool *data_ready_now)
{
	return vmci_trans(vsk)->notify_ops->poll_in(
			&vsk->sk, target, data_ready_now);
}
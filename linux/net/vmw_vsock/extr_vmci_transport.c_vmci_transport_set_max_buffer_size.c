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
struct TYPE_2__ {scalar_t__ queue_pair_size; scalar_t__ queue_pair_max_size; } ;

/* Variables and functions */
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 

__attribute__((used)) static void vmci_transport_set_max_buffer_size(struct vsock_sock *vsk,
					       u64 val)
{
	if (val < vmci_trans(vsk)->queue_pair_size)
		vmci_trans(vsk)->queue_pair_size = val;
	vmci_trans(vsk)->queue_pair_max_size = val;
}
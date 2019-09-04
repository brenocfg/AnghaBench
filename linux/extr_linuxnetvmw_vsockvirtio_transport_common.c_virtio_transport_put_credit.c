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
typedef  scalar_t__ u32 ;
struct virtio_vsock_sock {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void virtio_transport_put_credit(struct virtio_vsock_sock *vvs, u32 credit)
{
	spin_lock_bh(&vvs->tx_lock);
	vvs->tx_cnt -= credit;
	spin_unlock_bh(&vvs->tx_lock);
}
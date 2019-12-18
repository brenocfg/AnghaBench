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

/* Variables and functions */
 scalar_t__ __vsock_in_bound_table (struct vsock_sock*) ; 
 int /*<<< orphan*/  __vsock_remove_bound (struct vsock_sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsock_table_lock ; 

void vsock_remove_bound(struct vsock_sock *vsk)
{
	spin_lock_bh(&vsock_table_lock);
	if (__vsock_in_bound_table(vsk))
		__vsock_remove_bound(vsk);
	spin_unlock_bh(&vsock_table_lock);
}
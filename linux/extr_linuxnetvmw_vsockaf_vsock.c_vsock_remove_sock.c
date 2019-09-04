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
 scalar_t__ vsock_in_bound_table (struct vsock_sock*) ; 
 scalar_t__ vsock_in_connected_table (struct vsock_sock*) ; 
 int /*<<< orphan*/  vsock_remove_bound (struct vsock_sock*) ; 
 int /*<<< orphan*/  vsock_remove_connected (struct vsock_sock*) ; 

void vsock_remove_sock(struct vsock_sock *vsk)
{
	if (vsock_in_bound_table(vsk))
		vsock_remove_bound(vsk);

	if (vsock_in_connected_table(vsk))
		vsock_remove_connected(vsk);
}
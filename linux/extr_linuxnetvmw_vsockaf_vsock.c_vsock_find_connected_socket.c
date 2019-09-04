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
struct sockaddr_vm {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct sock* __vsock_find_connected_socket (struct sockaddr_vm*,struct sockaddr_vm*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsock_table_lock ; 

struct sock *vsock_find_connected_socket(struct sockaddr_vm *src,
					 struct sockaddr_vm *dst)
{
	struct sock *sk;

	spin_lock_bh(&vsock_table_lock);
	sk = __vsock_find_connected_socket(src, dst);
	if (sk)
		sock_hold(sk);

	spin_unlock_bh(&vsock_table_lock);

	return sk;
}
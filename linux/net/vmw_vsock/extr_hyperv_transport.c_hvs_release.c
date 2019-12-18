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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int hvs_close_lock_held (struct vsock_sock*) ; 
 int /*<<< orphan*/  lock_sock_nested (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct sock* sk_vsock (struct vsock_sock*) ; 
 int /*<<< orphan*/  vsock_remove_sock (struct vsock_sock*) ; 

__attribute__((used)) static void hvs_release(struct vsock_sock *vsk)
{
	struct sock *sk = sk_vsock(vsk);
	bool remove_sock;

	lock_sock_nested(sk, SINGLE_DEPTH_NESTING);
	remove_sock = hvs_close_lock_held(vsk);
	release_sock(sk);
	if (remove_sock)
		vsock_remove_sock(vsk);
}
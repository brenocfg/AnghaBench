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
struct vsock_sock {int /*<<< orphan*/  trans; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  hvs_shutdown_lock_held (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct sock* sk_vsock (struct vsock_sock*) ; 

__attribute__((used)) static int hvs_shutdown(struct vsock_sock *vsk, int mode)
{
	struct sock *sk = sk_vsock(vsk);

	if (!(mode & SEND_SHUTDOWN))
		return 0;

	lock_sock(sk);
	hvs_shutdown_lock_held(vsk->trans, mode);
	release_sock(sk);
	return 0;
}
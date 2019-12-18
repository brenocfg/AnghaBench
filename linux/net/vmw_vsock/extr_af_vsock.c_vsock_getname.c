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
struct vsock_sock {struct sockaddr_vm local_addr; struct sockaddr_vm remote_addr; } ;
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENOTCONN ; 
 scalar_t__ SS_CONNECTED ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr_vm*,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int vsock_getname(struct socket *sock,
			 struct sockaddr *addr, int peer)
{
	int err;
	struct sock *sk;
	struct vsock_sock *vsk;
	struct sockaddr_vm *vm_addr;

	sk = sock->sk;
	vsk = vsock_sk(sk);
	err = 0;

	lock_sock(sk);

	if (peer) {
		if (sock->state != SS_CONNECTED) {
			err = -ENOTCONN;
			goto out;
		}
		vm_addr = &vsk->remote_addr;
	} else {
		vm_addr = &vsk->local_addr;
	}

	if (!vm_addr) {
		err = -EINVAL;
		goto out;
	}

	/* sys_getsockname() and sys_getpeername() pass us a
	 * MAX_SOCK_ADDR-sized buffer and don't set addr_len.  Unfortunately
	 * that macro is defined in socket.c instead of .h, so we hardcode its
	 * value here.
	 */
	BUILD_BUG_ON(sizeof(*vm_addr) > 128);
	memcpy(addr, vm_addr, sizeof(*vm_addr));
	err = sizeof(*vm_addr);

out:
	release_sock(sk);
	return err;
}
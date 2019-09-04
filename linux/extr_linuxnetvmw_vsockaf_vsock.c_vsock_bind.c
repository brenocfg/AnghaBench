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
struct socket {struct sock* sk; } ;
struct sockaddr_vm {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int __vsock_bind (struct sock*,struct sockaddr_vm*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ vsock_addr_cast (struct sockaddr*,int,struct sockaddr_vm**) ; 

__attribute__((used)) static int
vsock_bind(struct socket *sock, struct sockaddr *addr, int addr_len)
{
	int err;
	struct sock *sk;
	struct sockaddr_vm *vm_addr;

	sk = sock->sk;

	if (vsock_addr_cast(addr, addr_len, &vm_addr) != 0)
		return -EINVAL;

	lock_sock(sk);
	err = __vsock_bind(sk, vm_addr);
	release_sock(sk);

	return err;
}
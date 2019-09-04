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
struct vsock_sock {int /*<<< orphan*/  local_addr; } ;
struct sockaddr_vm {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMADDR_CID_ANY ; 
 int /*<<< orphan*/  VMADDR_PORT_ANY ; 
 int __vsock_bind (struct sock*,struct sockaddr_vm*) ; 
 struct sock* sk_vsock (struct vsock_sock*) ; 
 scalar_t__ vsock_addr_bound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsock_addr_init (struct sockaddr_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsock_auto_bind(struct vsock_sock *vsk)
{
	struct sock *sk = sk_vsock(vsk);
	struct sockaddr_vm local_addr;

	if (vsock_addr_bound(&vsk->local_addr))
		return 0;
	vsock_addr_init(&local_addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);
	return __vsock_bind(sk, &local_addr);
}
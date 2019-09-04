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
struct vsock_sock {int /*<<< orphan*/  owner; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destruct ) (struct vsock_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VMADDR_CID_ANY ; 
 int /*<<< orphan*/  VMADDR_PORT_ANY ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vsock_sock*) ; 
 TYPE_1__* transport ; 
 int /*<<< orphan*/  vsock_addr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static void vsock_sk_destruct(struct sock *sk)
{
	struct vsock_sock *vsk = vsock_sk(sk);

	transport->destruct(vsk);

	/* When clearing these addresses, there's no need to set the family and
	 * possibly register the address family with the kernel.
	 */
	vsock_addr_init(&vsk->local_addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);
	vsock_addr_init(&vsk->remote_addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);

	put_cred(vsk->owner);
}
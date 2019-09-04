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
struct vsock_sock {int /*<<< orphan*/  remote_addr; } ;
struct socket {int /*<<< orphan*/  state; struct sock* sk; } ;
struct sockaddr_vm {scalar_t__ svm_family; int /*<<< orphan*/  svm_port; int /*<<< orphan*/  svm_cid; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dgram_allow ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  SS_CONNECTED ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  VMADDR_CID_ANY ; 
 int /*<<< orphan*/  VMADDR_PORT_ANY ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_vm*,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* transport ; 
 int vsock_addr_cast (struct sockaddr*,int,struct sockaddr_vm**) ; 
 int /*<<< orphan*/  vsock_addr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vsock_auto_bind (struct vsock_sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int vsock_dgram_connect(struct socket *sock,
			       struct sockaddr *addr, int addr_len, int flags)
{
	int err;
	struct sock *sk;
	struct vsock_sock *vsk;
	struct sockaddr_vm *remote_addr;

	sk = sock->sk;
	vsk = vsock_sk(sk);

	err = vsock_addr_cast(addr, addr_len, &remote_addr);
	if (err == -EAFNOSUPPORT && remote_addr->svm_family == AF_UNSPEC) {
		lock_sock(sk);
		vsock_addr_init(&vsk->remote_addr, VMADDR_CID_ANY,
				VMADDR_PORT_ANY);
		sock->state = SS_UNCONNECTED;
		release_sock(sk);
		return 0;
	} else if (err != 0)
		return -EINVAL;

	lock_sock(sk);

	err = vsock_auto_bind(vsk);
	if (err)
		goto out;

	if (!transport->dgram_allow(remote_addr->svm_cid,
				    remote_addr->svm_port)) {
		err = -EINVAL;
		goto out;
	}

	memcpy(&vsk->remote_addr, remote_addr, sizeof(vsk->remote_addr));
	sock->state = SS_CONNECTED;

out:
	release_sock(sk);
	return err;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vsock_sock {int /*<<< orphan*/  local_addr; } ;
struct sockaddr_vm {scalar_t__ svm_cid; } ;
struct sock {TYPE_1__* sk_socket; } ;
struct TYPE_4__ {scalar_t__ (* get_local_cid ) () ;} ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
#define  SOCK_DGRAM 129 
#define  SOCK_STREAM 128 
 scalar_t__ VMADDR_CID_ANY ; 
 int __vsock_bind_dgram (struct vsock_sock*,struct sockaddr_vm*) ; 
 int __vsock_bind_stream (struct vsock_sock*,struct sockaddr_vm*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 () ; 
 TYPE_2__* transport ; 
 scalar_t__ vsock_addr_bound (int /*<<< orphan*/ *) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 
 int /*<<< orphan*/  vsock_table_lock ; 

__attribute__((used)) static int __vsock_bind(struct sock *sk, struct sockaddr_vm *addr)
{
	struct vsock_sock *vsk = vsock_sk(sk);
	u32 cid;
	int retval;

	/* First ensure this socket isn't already bound. */
	if (vsock_addr_bound(&vsk->local_addr))
		return -EINVAL;

	/* Now bind to the provided address or select appropriate values if
	 * none are provided (VMADDR_CID_ANY and VMADDR_PORT_ANY).  Note that
	 * like AF_INET prevents binding to a non-local IP address (in most
	 * cases), we only allow binding to the local CID.
	 */
	cid = transport->get_local_cid();
	if (addr->svm_cid != cid && addr->svm_cid != VMADDR_CID_ANY)
		return -EADDRNOTAVAIL;

	switch (sk->sk_socket->type) {
	case SOCK_STREAM:
		spin_lock_bh(&vsock_table_lock);
		retval = __vsock_bind_stream(vsk, addr);
		spin_unlock_bh(&vsock_table_lock);
		break;

	case SOCK_DGRAM:
		retval = __vsock_bind_dgram(vsk, addr);
		break;

	default:
		retval = -EINVAL;
		break;
	}

	return retval;
}
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
struct sockaddr_vm {scalar_t__ svm_cid; int /*<<< orphan*/  svm_port; } ;
struct vsock_sock {struct sockaddr_vm remote_addr; } ;
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sock {int dummy; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_namelen; scalar_t__ msg_name; } ;
struct TYPE_2__ {scalar_t__ (* get_local_cid ) () ;int (* dgram_enqueue ) (struct vsock_sock*,struct sockaddr_vm*,struct msghdr*,size_t) ;int /*<<< orphan*/  (* dgram_allow ) (scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int MSG_OOB ; 
 scalar_t__ SS_CONNECTED ; 
 scalar_t__ VMADDR_CID_ANY ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ stub1 () ; 
 scalar_t__ stub2 () ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ) ; 
 int stub4 (struct vsock_sock*,struct sockaddr_vm*,struct msghdr*,size_t) ; 
 TYPE_1__* transport ; 
 int /*<<< orphan*/  vsock_addr_bound (struct sockaddr_vm*) ; 
 scalar_t__ vsock_addr_cast (scalar_t__,int /*<<< orphan*/ ,struct sockaddr_vm**) ; 
 int vsock_auto_bind (struct vsock_sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int vsock_dgram_sendmsg(struct socket *sock, struct msghdr *msg,
			       size_t len)
{
	int err;
	struct sock *sk;
	struct vsock_sock *vsk;
	struct sockaddr_vm *remote_addr;

	if (msg->msg_flags & MSG_OOB)
		return -EOPNOTSUPP;

	/* For now, MSG_DONTWAIT is always assumed... */
	err = 0;
	sk = sock->sk;
	vsk = vsock_sk(sk);

	lock_sock(sk);

	err = vsock_auto_bind(vsk);
	if (err)
		goto out;


	/* If the provided message contains an address, use that.  Otherwise
	 * fall back on the socket's remote handle (if it has been connected).
	 */
	if (msg->msg_name &&
	    vsock_addr_cast(msg->msg_name, msg->msg_namelen,
			    &remote_addr) == 0) {
		/* Ensure this address is of the right type and is a valid
		 * destination.
		 */

		if (remote_addr->svm_cid == VMADDR_CID_ANY)
			remote_addr->svm_cid = transport->get_local_cid();

		if (!vsock_addr_bound(remote_addr)) {
			err = -EINVAL;
			goto out;
		}
	} else if (sock->state == SS_CONNECTED) {
		remote_addr = &vsk->remote_addr;

		if (remote_addr->svm_cid == VMADDR_CID_ANY)
			remote_addr->svm_cid = transport->get_local_cid();

		/* XXX Should connect() or this function ensure remote_addr is
		 * bound?
		 */
		if (!vsock_addr_bound(&vsk->remote_addr)) {
			err = -EINVAL;
			goto out;
		}
	} else {
		err = -EINVAL;
		goto out;
	}

	if (!transport->dgram_allow(remote_addr->svm_cid,
				    remote_addr->svm_port)) {
		err = -EINVAL;
		goto out;
	}

	err = transport->dgram_enqueue(vsk, remote_addr, msg, len);

out:
	release_sock(sk);
	return err;
}
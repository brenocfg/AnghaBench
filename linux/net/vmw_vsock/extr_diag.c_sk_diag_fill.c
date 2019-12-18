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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  svm_port; int /*<<< orphan*/  svm_cid; } ;
struct TYPE_3__ {int /*<<< orphan*/  svm_port; int /*<<< orphan*/  svm_cid; } ;
struct vsock_sock {TYPE_2__ remote_addr; TYPE_1__ local_addr; } ;
struct vsock_diag_msg {int /*<<< orphan*/  vdiag_cookie; int /*<<< orphan*/  vdiag_ino; int /*<<< orphan*/  vdiag_dst_port; int /*<<< orphan*/  vdiag_dst_cid; int /*<<< orphan*/  vdiag_src_port; int /*<<< orphan*/  vdiag_src_cid; int /*<<< orphan*/  vdiag_shutdown; int /*<<< orphan*/  vdiag_state; int /*<<< orphan*/  vdiag_type; int /*<<< orphan*/  vdiag_family; } ;
struct sock {int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_type; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_VSOCK ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  SOCK_DIAG_BY_FAMILY ; 
 struct vsock_diag_msg* nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_diag_save_cookie (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_i_ino (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int sk_diag_fill(struct sock *sk, struct sk_buff *skb,
			u32 portid, u32 seq, u32 flags)
{
	struct vsock_sock *vsk = vsock_sk(sk);
	struct vsock_diag_msg *rep;
	struct nlmsghdr *nlh;

	nlh = nlmsg_put(skb, portid, seq, SOCK_DIAG_BY_FAMILY, sizeof(*rep),
			flags);
	if (!nlh)
		return -EMSGSIZE;

	rep = nlmsg_data(nlh);
	rep->vdiag_family = AF_VSOCK;

	/* Lock order dictates that sk_lock is acquired before
	 * vsock_table_lock, so we cannot lock here.  Simply don't take
	 * sk_lock; sk is guaranteed to stay alive since vsock_table_lock is
	 * held.
	 */
	rep->vdiag_type = sk->sk_type;
	rep->vdiag_state = sk->sk_state;
	rep->vdiag_shutdown = sk->sk_shutdown;
	rep->vdiag_src_cid = vsk->local_addr.svm_cid;
	rep->vdiag_src_port = vsk->local_addr.svm_port;
	rep->vdiag_dst_cid = vsk->remote_addr.svm_cid;
	rep->vdiag_dst_port = vsk->remote_addr.svm_port;
	rep->vdiag_ino = sock_i_ino(sk);

	sock_diag_save_cookie(sk, rep->vdiag_cookie);

	return 0;
}
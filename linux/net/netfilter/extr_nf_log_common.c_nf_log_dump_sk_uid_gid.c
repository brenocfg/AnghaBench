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
struct sock {int /*<<< orphan*/  sk_callback_lock; TYPE_1__* sk_socket; } ;
struct nf_log_buf {int dummy; } ;
struct net {int dummy; } ;
struct cred {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;
struct TYPE_4__ {struct cred* f_cred; } ;
struct TYPE_3__ {TYPE_2__* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_log_buf_add (struct nf_log_buf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_fullsock (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

void nf_log_dump_sk_uid_gid(struct net *net, struct nf_log_buf *m,
			    struct sock *sk)
{
	if (!sk || !sk_fullsock(sk) || !net_eq(net, sock_net(sk)))
		return;

	read_lock_bh(&sk->sk_callback_lock);
	if (sk->sk_socket && sk->sk_socket->file) {
		const struct cred *cred = sk->sk_socket->file->f_cred;
		nf_log_buf_add(m, "UID=%u GID=%u ",
			from_kuid_munged(&init_user_ns, cred->fsuid),
			from_kgid_munged(&init_user_ns, cred->fsgid));
	}
	read_unlock_bh(&sk->sk_callback_lock);
}
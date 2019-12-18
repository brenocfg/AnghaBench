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
struct sock {int /*<<< orphan*/  sk_callback_lock; TYPE_2__* sk_socket; } ;
struct sk_buff {int dummy; } ;
struct cred {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;
struct TYPE_4__ {TYPE_1__* file; } ;
struct TYPE_3__ {struct cred* f_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFQA_GID ; 
 int /*<<< orphan*/  NFQA_UID ; 
 int /*<<< orphan*/  from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_fullsock (struct sock*) ; 

__attribute__((used)) static int nfqnl_put_sk_uidgid(struct sk_buff *skb, struct sock *sk)
{
	const struct cred *cred;

	if (!sk_fullsock(sk))
		return 0;

	read_lock_bh(&sk->sk_callback_lock);
	if (sk->sk_socket && sk->sk_socket->file) {
		cred = sk->sk_socket->file->f_cred;
		if (nla_put_be32(skb, NFQA_UID,
		    htonl(from_kuid_munged(&init_user_ns, cred->fsuid))))
			goto nla_put_failure;
		if (nla_put_be32(skb, NFQA_GID,
		    htonl(from_kgid_munged(&init_user_ns, cred->fsgid))))
			goto nla_put_failure;
	}
	read_unlock_bh(&sk->sk_callback_lock);
	return 0;

nla_put_failure:
	read_unlock_bh(&sk->sk_callback_lock);
	return -1;
}
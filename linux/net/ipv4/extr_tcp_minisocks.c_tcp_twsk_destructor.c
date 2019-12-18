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
struct tcp_timewait_sock {scalar_t__ tw_md5_key; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_md5_needed ; 
 struct tcp_timewait_sock* tcp_twsk (struct sock*) ; 

void tcp_twsk_destructor(struct sock *sk)
{
#ifdef CONFIG_TCP_MD5SIG
	if (static_branch_unlikely(&tcp_md5_needed)) {
		struct tcp_timewait_sock *twsk = tcp_twsk(sk);

		if (twsk->tw_md5_key)
			kfree_rcu(twsk->tw_md5_key, rcu);
	}
#endif
}
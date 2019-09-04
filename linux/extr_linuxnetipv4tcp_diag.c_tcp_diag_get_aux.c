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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int tcp_diag_get_aux(struct sock *sk, bool net_admin,
			    struct sk_buff *skb)
{
#ifdef CONFIG_TCP_MD5SIG
	if (net_admin) {
		struct tcp_md5sig_info *md5sig;
		int err = 0;

		rcu_read_lock();
		md5sig = rcu_dereference(tcp_sk(sk)->md5sig_info);
		if (md5sig)
			err = tcp_diag_put_md5sig(skb, md5sig);
		rcu_read_unlock();
		if (err < 0)
			return err;
	}
#endif

	return 0;
}
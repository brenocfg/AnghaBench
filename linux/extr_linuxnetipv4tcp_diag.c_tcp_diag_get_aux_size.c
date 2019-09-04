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

/* Variables and functions */

__attribute__((used)) static size_t tcp_diag_get_aux_size(struct sock *sk, bool net_admin)
{
	size_t size = 0;

#ifdef CONFIG_TCP_MD5SIG
	if (net_admin && sk_fullsock(sk)) {
		const struct tcp_md5sig_info *md5sig;
		const struct tcp_md5sig_key *key;
		size_t md5sig_count = 0;

		rcu_read_lock();
		md5sig = rcu_dereference(tcp_sk(sk)->md5sig_info);
		if (md5sig) {
			hlist_for_each_entry_rcu(key, &md5sig->head, node)
				md5sig_count++;
		}
		rcu_read_unlock();
		size += nla_total_size(md5sig_count *
				       sizeof(struct tcp_diag_md5sig));
	}
#endif

	return size;
}
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
struct tcp_ulp_ops {int dummy; } ;
struct tcp_md5sig_info {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct inet_connection_sock {struct tcp_ulp_ops* icsk_ulp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  md5sig_info; } ;

/* Variables and functions */
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct tcp_md5sig_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int tcp_diag_put_md5sig (struct sk_buff*,struct tcp_md5sig_info*) ; 
 int tcp_diag_put_ulp (struct sk_buff*,struct sock*,struct tcp_ulp_ops const*) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 

__attribute__((used)) static int tcp_diag_get_aux(struct sock *sk, bool net_admin,
			    struct sk_buff *skb)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	int err = 0;

#ifdef CONFIG_TCP_MD5SIG
	if (net_admin) {
		struct tcp_md5sig_info *md5sig;

		rcu_read_lock();
		md5sig = rcu_dereference(tcp_sk(sk)->md5sig_info);
		if (md5sig)
			err = tcp_diag_put_md5sig(skb, md5sig);
		rcu_read_unlock();
		if (err < 0)
			return err;
	}
#endif

	if (net_admin) {
		const struct tcp_ulp_ops *ulp_ops;

		ulp_ops = icsk->icsk_ulp_ops;
		if (ulp_ops)
			err = tcp_diag_put_ulp(skb, sk, ulp_ops);
		if (err)
			return err;
	}
	return 0;
}
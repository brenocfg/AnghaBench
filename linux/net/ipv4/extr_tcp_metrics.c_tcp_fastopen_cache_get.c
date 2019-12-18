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
typedef  scalar_t__ u16 ;
struct tcp_fastopen_cookie {scalar_t__ len; int exp; } ;
struct tcp_fastopen_metrics {int try_exp; struct tcp_fastopen_cookie cookie; scalar_t__ mss; } ;
struct tcp_metrics_block {struct tcp_fastopen_metrics tcpm_fastopen; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sk_dst_get (struct sock*) ; 
 int /*<<< orphan*/  fastopen_seqlock ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 struct tcp_metrics_block* tcp_get_metrics (struct sock*,int /*<<< orphan*/ ,int) ; 

void tcp_fastopen_cache_get(struct sock *sk, u16 *mss,
			    struct tcp_fastopen_cookie *cookie)
{
	struct tcp_metrics_block *tm;

	rcu_read_lock();
	tm = tcp_get_metrics(sk, __sk_dst_get(sk), false);
	if (tm) {
		struct tcp_fastopen_metrics *tfom = &tm->tcpm_fastopen;
		unsigned int seq;

		do {
			seq = read_seqbegin(&fastopen_seqlock);
			if (tfom->mss)
				*mss = tfom->mss;
			*cookie = tfom->cookie;
			if (cookie->len <= 0 && tfom->try_exp == 1)
				cookie->exp = true;
		} while (read_seqretry(&fastopen_seqlock, seq));
	}
	rcu_read_unlock();
}
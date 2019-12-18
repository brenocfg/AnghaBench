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
struct sock {int /*<<< orphan*/  sk_filter; } ;
struct sk_filter {int /*<<< orphan*/  prog; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int bpf_prog_run_clear_cb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_filter* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static unsigned int run_filter(struct sk_buff *skb,
			       const struct sock *sk,
			       unsigned int res)
{
	struct sk_filter *filter;

	rcu_read_lock();
	filter = rcu_dereference(sk->sk_filter);
	if (filter != NULL)
		res = bpf_prog_run_clear_cb(filter->prog, skb);
	rcu_read_unlock();

	return res;
}
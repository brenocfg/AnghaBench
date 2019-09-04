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
struct sock {int sk_pacing_rate; int sk_pacing_shift; int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_tsq_flags; } ;
struct sk_buff {int truesize; } ;
struct TYPE_3__ {int /*<<< orphan*/  sysctl_tcp_limit_output_bytes; } ;
struct TYPE_4__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSQ_THROTTLED ; 
 unsigned int max (int,int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 TYPE_2__* sock_net (struct sock*) ; 
 scalar_t__ tcp_rtx_queue_empty (struct sock*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static bool tcp_small_queue_check(struct sock *sk, const struct sk_buff *skb,
				  unsigned int factor)
{
	unsigned int limit;

	limit = max(2 * skb->truesize, sk->sk_pacing_rate >> sk->sk_pacing_shift);
	limit = min_t(u32, limit,
		      sock_net(sk)->ipv4.sysctl_tcp_limit_output_bytes);
	limit <<= factor;

	if (refcount_read(&sk->sk_wmem_alloc) > limit) {
		/* Always send skb if rtx queue is empty.
		 * No need to wait for TX completion to call us back,
		 * after softirq/tasklet schedule.
		 * This helps when TX completions are delayed too much.
		 */
		if (tcp_rtx_queue_empty(sk))
			return false;

		set_bit(TSQ_THROTTLED, &sk->sk_tsq_flags);
		/* It is possible TX completion already happened
		 * before we set TSQ_THROTTLED, so we must
		 * test again the condition.
		 */
		smp_mb__after_atomic();
		if (refcount_read(&sk->sk_wmem_alloc) > limit)
			return true;
	}
	return false;
}
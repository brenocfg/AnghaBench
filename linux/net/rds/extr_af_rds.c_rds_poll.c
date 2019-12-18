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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_error_queue; scalar_t__ sk_err; } ;
struct TYPE_2__ {int /*<<< orphan*/  zcookie_head; } ;
struct rds_sock {scalar_t__ rs_snd_bytes; scalar_t__ rs_seen_congestion; int /*<<< orphan*/  rs_recv_lock; TYPE_1__ rs_zcookie_queue; int /*<<< orphan*/  rs_notify_queue; int /*<<< orphan*/  rs_recv_queue; int /*<<< orphan*/  rs_lock; scalar_t__ rs_cong_notify; int /*<<< orphan*/  rs_cong_track; int /*<<< orphan*/  rs_cong_monitor; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRBAND ; 
 int EPOLLWRNORM ; 
 int POLLERR ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rds_cong_updated_since (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_poll_waitq ; 
 scalar_t__ rds_sk_sndbuf (struct rds_sock*) ; 
 struct rds_sock* rds_sk_to_rs (struct sock*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t rds_poll(struct file *file, struct socket *sock,
			     poll_table *wait)
{
	struct sock *sk = sock->sk;
	struct rds_sock *rs = rds_sk_to_rs(sk);
	__poll_t mask = 0;
	unsigned long flags;

	poll_wait(file, sk_sleep(sk), wait);

	if (rs->rs_seen_congestion)
		poll_wait(file, &rds_poll_waitq, wait);

	read_lock_irqsave(&rs->rs_recv_lock, flags);
	if (!rs->rs_cong_monitor) {
		/* When a congestion map was updated, we signal EPOLLIN for
		 * "historical" reasons. Applications can also poll for
		 * WRBAND instead. */
		if (rds_cong_updated_since(&rs->rs_cong_track))
			mask |= (EPOLLIN | EPOLLRDNORM | EPOLLWRBAND);
	} else {
		spin_lock(&rs->rs_lock);
		if (rs->rs_cong_notify)
			mask |= (EPOLLIN | EPOLLRDNORM);
		spin_unlock(&rs->rs_lock);
	}
	if (!list_empty(&rs->rs_recv_queue) ||
	    !list_empty(&rs->rs_notify_queue) ||
	    !list_empty(&rs->rs_zcookie_queue.zcookie_head))
		mask |= (EPOLLIN | EPOLLRDNORM);
	if (rs->rs_snd_bytes < rds_sk_sndbuf(rs))
		mask |= (EPOLLOUT | EPOLLWRNORM);
	if (sk->sk_err || !skb_queue_empty(&sk->sk_error_queue))
		mask |= POLLERR;
	read_unlock_irqrestore(&rs->rs_recv_lock, flags);

	/* clear state any time we wake a seen-congested socket */
	if (mask)
		rs->rs_seen_congestion = 0;

	return mask;
}
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
struct tcp_metrics_block {int dummy; } ;
struct request_sock {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_METRIC_RTT ; 
 struct tcp_metrics_block* __tcp_get_metrics_req (struct request_sock*,struct dst_entry*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ tcp_metric_get (struct tcp_metrics_block*,int /*<<< orphan*/ ) ; 

bool tcp_peer_is_proven(struct request_sock *req, struct dst_entry *dst)
{
	struct tcp_metrics_block *tm;
	bool ret;

	if (!dst)
		return false;

	rcu_read_lock();
	tm = __tcp_get_metrics_req(req, dst);
	if (tm && tcp_metric_get(tm, TCP_METRIC_RTT))
		ret = true;
	else
		ret = false;
	rcu_read_unlock();

	return ret;
}
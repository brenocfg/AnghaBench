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
struct sock {scalar_t__ sk_clockid; scalar_t__ sk_txtime_deadline_mode; } ;
struct sk_buff {struct sock* sk; int /*<<< orphan*/  tstamp; } ;
struct etf_sched_data {scalar_t__ clockid; scalar_t__ deadline_mode; int /*<<< orphan*/  last; int /*<<< orphan*/  (* get_time ) () ;scalar_t__ skip_sock_check; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_TXTIME ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct etf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static bool is_packet_valid(struct Qdisc *sch, struct sk_buff *nskb)
{
	struct etf_sched_data *q = qdisc_priv(sch);
	ktime_t txtime = nskb->tstamp;
	struct sock *sk = nskb->sk;
	ktime_t now;

	if (q->skip_sock_check)
		goto skip;

	if (!sk)
		return false;

	if (!sock_flag(sk, SOCK_TXTIME))
		return false;

	/* We don't perform crosstimestamping.
	 * Drop if packet's clockid differs from qdisc's.
	 */
	if (sk->sk_clockid != q->clockid)
		return false;

	if (sk->sk_txtime_deadline_mode != q->deadline_mode)
		return false;

skip:
	now = q->get_time();
	if (ktime_before(txtime, now) || ktime_before(txtime, q->last))
		return false;

	return true;
}
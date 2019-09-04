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
typedef  int /*<<< orphan*/  tv ;
typedef  int /*<<< orphan*/  tss ;
typedef  int /*<<< orphan*/  ts ;
struct timeval {scalar_t__ ts; } ;
struct timespec {scalar_t__ ts; } ;
struct sock {int sk_tsflags; } ;
struct skb_shared_hwtstamps {scalar_t__ hwtstamp; } ;
struct sk_buff {scalar_t__ tstamp; int len; struct timeval* data; } ;
struct scm_timestamping {scalar_t__ ts; } ;
struct msghdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ opt_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCM_TIMESTAMP ; 
 int /*<<< orphan*/  SCM_TIMESTAMPING ; 
 int /*<<< orphan*/  SCM_TIMESTAMPING_OPT_STATS ; 
 int /*<<< orphan*/  SCM_TIMESTAMPNS ; 
 TYPE_1__* SKB_EXT_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SOCK_RCVTSTAMP ; 
 int /*<<< orphan*/  SOCK_RCVTSTAMPNS ; 
 int SOF_TIMESTAMPING_OPT_PKTINFO ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_SOFTWARE ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 scalar_t__ ktime_to_timespec_cond (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct timeval*) ; 
 int /*<<< orphan*/  put_ts_pktinfo (struct msghdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_get_timestamp (struct sk_buff*,struct timeval*) ; 
 int /*<<< orphan*/  skb_get_timestampns (struct sk_buff*,struct timeval*) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 scalar_t__ skb_is_err_queue (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_swtx_tstamp (struct sk_buff*,int) ; 
 int sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

void __sock_recv_timestamp(struct msghdr *msg, struct sock *sk,
	struct sk_buff *skb)
{
	int need_software_tstamp = sock_flag(sk, SOCK_RCVTSTAMP);
	struct scm_timestamping tss;
	int empty = 1, false_tstamp = 0;
	struct skb_shared_hwtstamps *shhwtstamps =
		skb_hwtstamps(skb);

	/* Race occurred between timestamp enabling and packet
	   receiving.  Fill in the current time for now. */
	if (need_software_tstamp && skb->tstamp == 0) {
		__net_timestamp(skb);
		false_tstamp = 1;
	}

	if (need_software_tstamp) {
		if (!sock_flag(sk, SOCK_RCVTSTAMPNS)) {
			struct timeval tv;
			skb_get_timestamp(skb, &tv);
			put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMP,
				 sizeof(tv), &tv);
		} else {
			struct timespec ts;
			skb_get_timestampns(skb, &ts);
			put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMPNS,
				 sizeof(ts), &ts);
		}
	}

	memset(&tss, 0, sizeof(tss));
	if ((sk->sk_tsflags & SOF_TIMESTAMPING_SOFTWARE) &&
	    ktime_to_timespec_cond(skb->tstamp, tss.ts + 0))
		empty = 0;
	if (shhwtstamps &&
	    (sk->sk_tsflags & SOF_TIMESTAMPING_RAW_HARDWARE) &&
	    !skb_is_swtx_tstamp(skb, false_tstamp) &&
	    ktime_to_timespec_cond(shhwtstamps->hwtstamp, tss.ts + 2)) {
		empty = 0;
		if ((sk->sk_tsflags & SOF_TIMESTAMPING_OPT_PKTINFO) &&
		    !skb_is_err_queue(skb))
			put_ts_pktinfo(msg, skb);
	}
	if (!empty) {
		put_cmsg(msg, SOL_SOCKET,
			 SCM_TIMESTAMPING, sizeof(tss), &tss);

		if (skb_is_err_queue(skb) && skb->len &&
		    SKB_EXT_ERR(skb)->opt_stats)
			put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMPING_OPT_STATS,
				 skb->len, skb->data);
	}
}
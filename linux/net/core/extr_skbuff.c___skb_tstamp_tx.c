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
struct sock {int sk_tsflags; scalar_t__ sk_protocol; scalar_t__ sk_type; } ;
struct skb_shared_hwtstamps {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  tstamp; } ;
struct TYPE_2__ {int tx_flags; int /*<<< orphan*/  tskey; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPPROTO_TCP ; 
 int SKBTX_ANY_TSTAMP ; 
 int SKBTX_IN_PROGRESS ; 
 scalar_t__ SOCK_STREAM ; 
 int SOF_TIMESTAMPING_OPT_STATS ; 
 int SOF_TIMESTAMPING_OPT_TSONLY ; 
 int SOF_TIMESTAMPING_OPT_TX_SWHW ; 
 int /*<<< orphan*/  __skb_complete_tx_timestamp (struct sk_buff*,struct sock*,int,int) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_may_tx_timestamp (struct sock*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 struct sk_buff* tcp_get_timestamping_opt_stats (struct sock*) ; 

void __skb_tstamp_tx(struct sk_buff *orig_skb,
		     struct skb_shared_hwtstamps *hwtstamps,
		     struct sock *sk, int tstype)
{
	struct sk_buff *skb;
	bool tsonly, opt_stats = false;

	if (!sk)
		return;

	if (!hwtstamps && !(sk->sk_tsflags & SOF_TIMESTAMPING_OPT_TX_SWHW) &&
	    skb_shinfo(orig_skb)->tx_flags & SKBTX_IN_PROGRESS)
		return;

	tsonly = sk->sk_tsflags & SOF_TIMESTAMPING_OPT_TSONLY;
	if (!skb_may_tx_timestamp(sk, tsonly))
		return;

	if (tsonly) {
#ifdef CONFIG_INET
		if ((sk->sk_tsflags & SOF_TIMESTAMPING_OPT_STATS) &&
		    sk->sk_protocol == IPPROTO_TCP &&
		    sk->sk_type == SOCK_STREAM) {
			skb = tcp_get_timestamping_opt_stats(sk);
			opt_stats = true;
		} else
#endif
			skb = alloc_skb(0, GFP_ATOMIC);
	} else {
		skb = skb_clone(orig_skb, GFP_ATOMIC);
	}
	if (!skb)
		return;

	if (tsonly) {
		skb_shinfo(skb)->tx_flags |= skb_shinfo(orig_skb)->tx_flags &
					     SKBTX_ANY_TSTAMP;
		skb_shinfo(skb)->tskey = skb_shinfo(orig_skb)->tskey;
	}

	if (hwtstamps)
		*skb_hwtstamps(skb) = *hwtstamps;
	else
		skb->tstamp = ktime_get_real();

	__skb_complete_tx_timestamp(skb, sk, tstype, opt_stats);
}
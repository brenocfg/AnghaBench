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
typedef  int /*<<< orphan*/  u64 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct cpts {int dummy; } ;
typedef  int /*<<< orphan*/  ssh ;
struct TYPE_2__ {int tx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTS_EV_TX ; 
 int SKBTX_IN_PROGRESS ; 
 int /*<<< orphan*/  cpts_find_ts (struct cpts*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 

void cpts_tx_timestamp(struct cpts *cpts, struct sk_buff *skb)
{
	u64 ns;
	struct skb_shared_hwtstamps ssh;

	if (!(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS))
		return;
	ns = cpts_find_ts(cpts, skb, CPTS_EV_TX);
	if (!ns)
		return;
	memset(&ssh, 0, sizeof(ssh));
	ssh.hwtstamp = ns_to_ktime(ns);
	skb_tstamp_tx(skb, &ssh);
}
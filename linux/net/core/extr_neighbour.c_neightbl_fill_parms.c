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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct neigh_parms {int reachable_time; int /*<<< orphan*/  refcnt; TYPE_1__* dev; } ;
struct TYPE_2__ {int ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANYCAST_DELAY ; 
 int /*<<< orphan*/  APP_PROBES ; 
 int /*<<< orphan*/  BASE_REACHABLE_TIME ; 
 int /*<<< orphan*/  DELAY_PROBE_TIME ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_FRAME_LEN ; 
 int /*<<< orphan*/  GC_STALETIME ; 
 int /*<<< orphan*/  LOCKTIME ; 
 int /*<<< orphan*/  MCAST_PROBES ; 
 int /*<<< orphan*/  MCAST_REPROBES ; 
 int /*<<< orphan*/  NDTA_PARMS ; 
 int /*<<< orphan*/  NDTPA_ANYCAST_DELAY ; 
 int /*<<< orphan*/  NDTPA_APP_PROBES ; 
 int /*<<< orphan*/  NDTPA_BASE_REACHABLE_TIME ; 
 int /*<<< orphan*/  NDTPA_DELAY_PROBE_TIME ; 
 int /*<<< orphan*/  NDTPA_GC_STALETIME ; 
 int /*<<< orphan*/  NDTPA_IFINDEX ; 
 int /*<<< orphan*/  NDTPA_LOCKTIME ; 
 int /*<<< orphan*/  NDTPA_MCAST_PROBES ; 
 int /*<<< orphan*/  NDTPA_MCAST_REPROBES ; 
 int /*<<< orphan*/  NDTPA_PAD ; 
 int /*<<< orphan*/  NDTPA_PROXY_DELAY ; 
 int /*<<< orphan*/  NDTPA_PROXY_QLEN ; 
 int /*<<< orphan*/  NDTPA_QUEUE_LEN ; 
 int /*<<< orphan*/  NDTPA_QUEUE_LENBYTES ; 
 int /*<<< orphan*/  NDTPA_REACHABLE_TIME ; 
 int /*<<< orphan*/  NDTPA_REFCNT ; 
 int /*<<< orphan*/  NDTPA_RETRANS_TIME ; 
 int /*<<< orphan*/  NDTPA_UCAST_PROBES ; 
 int NEIGH_VAR (struct neigh_parms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROXY_DELAY ; 
 int /*<<< orphan*/  PROXY_QLEN ; 
 int /*<<< orphan*/  QUEUE_LEN_BYTES ; 
 int /*<<< orphan*/  RETRANS_TIME ; 
 int SKB_TRUESIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCAST_PROBES ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_msecs (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int neightbl_fill_parms(struct sk_buff *skb, struct neigh_parms *parms)
{
	struct nlattr *nest;

	nest = nla_nest_start_noflag(skb, NDTA_PARMS);
	if (nest == NULL)
		return -ENOBUFS;

	if ((parms->dev &&
	     nla_put_u32(skb, NDTPA_IFINDEX, parms->dev->ifindex)) ||
	    nla_put_u32(skb, NDTPA_REFCNT, refcount_read(&parms->refcnt)) ||
	    nla_put_u32(skb, NDTPA_QUEUE_LENBYTES,
			NEIGH_VAR(parms, QUEUE_LEN_BYTES)) ||
	    /* approximative value for deprecated QUEUE_LEN (in packets) */
	    nla_put_u32(skb, NDTPA_QUEUE_LEN,
			NEIGH_VAR(parms, QUEUE_LEN_BYTES) / SKB_TRUESIZE(ETH_FRAME_LEN)) ||
	    nla_put_u32(skb, NDTPA_PROXY_QLEN, NEIGH_VAR(parms, PROXY_QLEN)) ||
	    nla_put_u32(skb, NDTPA_APP_PROBES, NEIGH_VAR(parms, APP_PROBES)) ||
	    nla_put_u32(skb, NDTPA_UCAST_PROBES,
			NEIGH_VAR(parms, UCAST_PROBES)) ||
	    nla_put_u32(skb, NDTPA_MCAST_PROBES,
			NEIGH_VAR(parms, MCAST_PROBES)) ||
	    nla_put_u32(skb, NDTPA_MCAST_REPROBES,
			NEIGH_VAR(parms, MCAST_REPROBES)) ||
	    nla_put_msecs(skb, NDTPA_REACHABLE_TIME, parms->reachable_time,
			  NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_BASE_REACHABLE_TIME,
			  NEIGH_VAR(parms, BASE_REACHABLE_TIME), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_GC_STALETIME,
			  NEIGH_VAR(parms, GC_STALETIME), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_DELAY_PROBE_TIME,
			  NEIGH_VAR(parms, DELAY_PROBE_TIME), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_RETRANS_TIME,
			  NEIGH_VAR(parms, RETRANS_TIME), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_ANYCAST_DELAY,
			  NEIGH_VAR(parms, ANYCAST_DELAY), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_PROXY_DELAY,
			  NEIGH_VAR(parms, PROXY_DELAY), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_LOCKTIME,
			  NEIGH_VAR(parms, LOCKTIME), NDTPA_PAD))
		goto nla_put_failure;
	return nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -EMSGSIZE;
}
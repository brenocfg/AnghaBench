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
typedef  int /*<<< orphan*/  ts_pktinfo ;
struct sk_buff {scalar_t__ len; } ;
struct scm_ts_pktinfo {scalar_t__ pkt_length; int /*<<< orphan*/  if_index; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCM_TIMESTAMPING_PKTINFO ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 struct net_device* dev_get_by_napi_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct scm_ts_pktinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct scm_ts_pktinfo*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff*) ; 
 scalar_t__ skb_mac_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_napi_id (struct sk_buff*) ; 

__attribute__((used)) static void put_ts_pktinfo(struct msghdr *msg, struct sk_buff *skb)
{
	struct scm_ts_pktinfo ts_pktinfo;
	struct net_device *orig_dev;

	if (!skb_mac_header_was_set(skb))
		return;

	memset(&ts_pktinfo, 0, sizeof(ts_pktinfo));

	rcu_read_lock();
	orig_dev = dev_get_by_napi_id(skb_napi_id(skb));
	if (orig_dev)
		ts_pktinfo.if_index = orig_dev->ifindex;
	rcu_read_unlock();

	ts_pktinfo.pkt_length = skb->len - skb_mac_offset(skb);
	put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMPING_PKTINFO,
		 sizeof(ts_pktinfo), &ts_pktinfo);
}
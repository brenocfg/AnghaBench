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
struct nl_pktinfo {int /*<<< orphan*/  group; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_2__ {int /*<<< orphan*/  dst_group; } ;

/* Variables and functions */
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NETLINK_PKTINFO ; 
 int /*<<< orphan*/  SOL_NETLINK ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nl_pktinfo*) ; 

__attribute__((used)) static void netlink_cmsg_recv_pktinfo(struct msghdr *msg, struct sk_buff *skb)
{
	struct nl_pktinfo info;

	info.group = NETLINK_CB(skb).dst_group;
	put_cmsg(msg, SOL_NETLINK, NETLINK_PKTINFO, sizeof(info), &info);
}
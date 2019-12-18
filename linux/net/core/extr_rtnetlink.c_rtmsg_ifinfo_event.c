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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {scalar_t__ reg_state; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 struct sk_buff* rtmsg_ifinfo_build_skb (int,struct net_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  rtmsg_ifinfo_send (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtmsg_ifinfo_event(int type, struct net_device *dev,
			       unsigned int change, u32 event,
			       gfp_t flags, int *new_nsid, int new_ifindex)
{
	struct sk_buff *skb;

	if (dev->reg_state != NETREG_REGISTERED)
		return;

	skb = rtmsg_ifinfo_build_skb(type, dev, change, event, flags, new_nsid,
				     new_ifindex);
	if (skb)
		rtmsg_ifinfo_send(skb, dev, flags);
}
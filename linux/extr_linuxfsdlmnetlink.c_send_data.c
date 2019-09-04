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
struct sk_buff {scalar_t__ data; } ;
struct nlmsghdr {int dummy; } ;
struct genlmsghdr {int dummy; } ;

/* Variables and functions */
 void* genlmsg_data (struct genlmsghdr*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_unicast (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  listener_nlportid ; 
 struct genlmsghdr* nlmsg_data (struct nlmsghdr*) ; 

__attribute__((used)) static int send_data(struct sk_buff *skb)
{
	struct genlmsghdr *genlhdr = nlmsg_data((struct nlmsghdr *)skb->data);
	void *data = genlmsg_data(genlhdr);

	genlmsg_end(skb, data);

	return genlmsg_unicast(&init_net, skb, listener_nlportid);
}
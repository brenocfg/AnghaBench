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
struct sk_buff {int dummy; } ;
struct genlmsghdr {int dummy; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 void* genlmsg_data (struct genlmsghdr*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 struct genlmsghdr* nlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_hdr (struct sk_buff*) ; 

__attribute__((used)) static int send_reply(struct sk_buff *skb, struct genl_info *info)
{
	struct genlmsghdr *genlhdr = nlmsg_data(nlmsg_hdr(skb));
	void *reply = genlmsg_data(genlhdr);

	genlmsg_end(skb, reply);

	return genlmsg_reply(skb, info);
}
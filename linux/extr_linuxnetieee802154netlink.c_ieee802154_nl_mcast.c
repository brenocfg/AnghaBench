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
struct nlmsghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* genlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_multicast (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl802154_family ; 
 int /*<<< orphan*/  nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 

int ieee802154_nl_mcast(struct sk_buff *msg, unsigned int group)
{
	struct nlmsghdr *nlh = nlmsg_hdr(msg);
	void *hdr = genlmsg_data(nlmsg_data(nlh));

	genlmsg_end(msg, hdr);

	return genlmsg_multicast(&nl802154_family, msg, 0, group, GFP_ATOMIC);
}
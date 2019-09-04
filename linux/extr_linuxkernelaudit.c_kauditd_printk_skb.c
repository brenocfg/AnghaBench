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
struct nlmsghdr {scalar_t__ nlmsg_type; } ;

/* Variables and functions */
 scalar_t__ AUDIT_EOE ; 
 char* nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_notice (char*,scalar_t__,char*) ; 
 scalar_t__ printk_ratelimit () ; 

__attribute__((used)) static void kauditd_printk_skb(struct sk_buff *skb)
{
	struct nlmsghdr *nlh = nlmsg_hdr(skb);
	char *data = nlmsg_data(nlh);

	if (nlh->nlmsg_type != AUDIT_EOE && printk_ratelimit())
		pr_notice("type=%d %s\n", nlh->nlmsg_type, data);
}
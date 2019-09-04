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
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfnl_ct_hook {scalar_t__ (* parse ) (struct nlattr const* const,struct nf_conn*) ;int /*<<< orphan*/  (* attach_expect ) (struct nlattr const* const,struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct nf_conn* (* get_ct ) (int /*<<< orphan*/ ,int*) ;} ;
struct nf_queue_entry {int /*<<< orphan*/  skb; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 TYPE_1__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 size_t NFQA_CT ; 
 size_t NFQA_EXP ; 
 int /*<<< orphan*/  nlmsg_report (struct nlmsghdr const*) ; 
 struct nf_conn* stub1 (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct nlattr const* const,struct nf_conn*) ; 
 int /*<<< orphan*/  stub3 (struct nlattr const* const,struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nf_conn *nfqnl_ct_parse(struct nfnl_ct_hook *nfnl_ct,
				      const struct nlmsghdr *nlh,
				      const struct nlattr * const nfqa[],
				      struct nf_queue_entry *entry,
				      enum ip_conntrack_info *ctinfo)
{
	struct nf_conn *ct;

	ct = nfnl_ct->get_ct(entry->skb, ctinfo);
	if (ct == NULL)
		return NULL;

	if (nfnl_ct->parse(nfqa[NFQA_CT], ct) < 0)
		return NULL;

	if (nfqa[NFQA_EXP])
		nfnl_ct->attach_expect(nfqa[NFQA_EXP], ct,
				      NETLINK_CB(entry->skb).portid,
				      nlmsg_report(nlh));
	return ct;
}
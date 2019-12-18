#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {void* ip; } ;
struct nf_nat_range2 {int flags; int /*<<< orphan*/  max_proto; int /*<<< orphan*/  min_proto; TYPE_2__ max_addr; TYPE_2__ min_addr; } ;
struct nf_nat_ipv4_multi_range_compat {TYPE_1__* range; } ;
struct nf_conn {int dummy; } ;
struct in_ifaddr {void* ifa_local; } ;
struct in_device {int /*<<< orphan*/  ifa_list; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  void* __be32 ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int IP_CT_NEW ; 
 int IP_CT_RELATED ; 
 unsigned int NF_DROP ; 
 unsigned int NF_INET_LOCAL_OUT ; 
 unsigned int NF_INET_PRE_ROUTING ; 
 int /*<<< orphan*/  NF_NAT_MANIP_DST ; 
 int NF_NAT_RANGE_MAP_IPS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct in_device* __in_dev_get_rcu (int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 unsigned int nf_nat_setup_info (struct nf_conn*,struct nf_nat_range2*,int /*<<< orphan*/ ) ; 
 struct in_ifaddr* rcu_dereference (int /*<<< orphan*/ ) ; 

unsigned int
nf_nat_redirect_ipv4(struct sk_buff *skb,
		     const struct nf_nat_ipv4_multi_range_compat *mr,
		     unsigned int hooknum)
{
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	__be32 newdst;
	struct nf_nat_range2 newrange;

	WARN_ON(hooknum != NF_INET_PRE_ROUTING &&
		hooknum != NF_INET_LOCAL_OUT);

	ct = nf_ct_get(skb, &ctinfo);
	WARN_ON(!(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED)));

	/* Local packets: make them go to loopback */
	if (hooknum == NF_INET_LOCAL_OUT) {
		newdst = htonl(0x7F000001);
	} else {
		const struct in_device *indev;

		newdst = 0;

		indev = __in_dev_get_rcu(skb->dev);
		if (indev) {
			const struct in_ifaddr *ifa;

			ifa = rcu_dereference(indev->ifa_list);
			if (ifa)
				newdst = ifa->ifa_local;
		}

		if (!newdst)
			return NF_DROP;
	}

	/* Transfer from original range. */
	memset(&newrange.min_addr, 0, sizeof(newrange.min_addr));
	memset(&newrange.max_addr, 0, sizeof(newrange.max_addr));
	newrange.flags	     = mr->range[0].flags | NF_NAT_RANGE_MAP_IPS;
	newrange.min_addr.ip = newdst;
	newrange.max_addr.ip = newdst;
	newrange.min_proto   = mr->range[0].min;
	newrange.max_proto   = mr->range[0].max;

	/* Hand modified range to generic setup. */
	return nf_nat_setup_info(ct, &newrange, NF_NAT_MANIP_DST);
}
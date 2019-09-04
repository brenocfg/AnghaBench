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
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct mpls_link_stats {int dummy; } ;
struct mpls_dev {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENODATA ; 
 int /*<<< orphan*/  MPLS_STATS_LINK ; 
 int /*<<< orphan*/  MPLS_STATS_UNSPEC ; 
 struct mpls_dev* mpls_dev_get (struct net_device const*) ; 
 int /*<<< orphan*/  mpls_get_stats (struct mpls_dev*,struct mpls_link_stats*) ; 
 struct mpls_link_stats* nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpls_fill_stats_af(struct sk_buff *skb,
			      const struct net_device *dev)
{
	struct mpls_link_stats *stats;
	struct mpls_dev *mdev;
	struct nlattr *nla;

	mdev = mpls_dev_get(dev);
	if (!mdev)
		return -ENODATA;

	nla = nla_reserve_64bit(skb, MPLS_STATS_LINK,
				sizeof(struct mpls_link_stats),
				MPLS_STATS_UNSPEC);
	if (!nla)
		return -EMSGSIZE;

	stats = nla_data(nla);
	mpls_get_stats(mdev, stats);

	return 0;
}
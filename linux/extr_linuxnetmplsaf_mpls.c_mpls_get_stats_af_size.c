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
struct net_device {int dummy; } ;
struct mpls_link_stats {int dummy; } ;
struct mpls_dev {int dummy; } ;

/* Variables and functions */
 struct mpls_dev* mpls_dev_get (struct net_device const*) ; 
 size_t nla_total_size_64bit (int) ; 

__attribute__((used)) static size_t mpls_get_stats_af_size(const struct net_device *dev)
{
	struct mpls_dev *mdev;

	mdev = mpls_dev_get(dev);
	if (!mdev)
		return 0;

	return nla_total_size_64bit(sizeof(struct mpls_link_stats));
}
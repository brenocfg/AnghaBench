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
struct nlattr {int dummy; } ;
struct ctnetlink_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct ctnetlink_filter* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ctnetlink_filter *
ctnetlink_alloc_filter(const struct nlattr * const cda[])
{
#ifdef CONFIG_NF_CONNTRACK_MARK
	struct ctnetlink_filter *filter;

	filter = kzalloc(sizeof(*filter), GFP_KERNEL);
	if (filter == NULL)
		return ERR_PTR(-ENOMEM);

	filter->mark.val = ntohl(nla_get_be32(cda[CTA_MARK]));
	filter->mark.mask = ntohl(nla_get_be32(cda[CTA_MARK_MASK]));

	return filter;
#else
	return ERR_PTR(-EOPNOTSUPP);
#endif
}
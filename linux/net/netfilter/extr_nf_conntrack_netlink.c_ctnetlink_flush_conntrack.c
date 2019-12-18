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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct ctnetlink_filter {int dummy; } ;

/* Variables and functions */
 size_t CTA_MARK ; 
 size_t CTA_MARK_MASK ; 
 scalar_t__ IS_ERR (struct ctnetlink_filter*) ; 
 int PTR_ERR (struct ctnetlink_filter*) ; 
 struct ctnetlink_filter* ctnetlink_alloc_filter (struct nlattr const* const*,scalar_t__) ; 
 int /*<<< orphan*/  ctnetlink_flush_iterate ; 
 int /*<<< orphan*/  kfree (struct ctnetlink_filter*) ; 
 int /*<<< orphan*/  nf_ct_iterate_cleanup_net (struct net*,int /*<<< orphan*/ ,struct ctnetlink_filter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ctnetlink_flush_conntrack(struct net *net,
				     const struct nlattr * const cda[],
				     u32 portid, int report, u8 family)
{
	struct ctnetlink_filter *filter = NULL;

	if (family || (cda[CTA_MARK] && cda[CTA_MARK_MASK])) {
		filter = ctnetlink_alloc_filter(cda, family);
		if (IS_ERR(filter))
			return PTR_ERR(filter);
	}

	nf_ct_iterate_cleanup_net(net, ctnetlink_flush_iterate, filter,
				  portid, report);
	kfree(filter);

	return 0;
}
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
typedef  int /*<<< orphan*/  u64 ;
struct nd_region {struct nd_interleave_set* nd_set; } ;
struct nd_namespace_index {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct nd_interleave_set {int /*<<< orphan*/  cookie2; int /*<<< orphan*/  cookie1; } ;

/* Variables and functions */
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 

u64 nd_region_interleave_set_cookie(struct nd_region *nd_region,
		struct nd_namespace_index *nsindex)
{
	struct nd_interleave_set *nd_set = nd_region->nd_set;

	if (!nd_set)
		return 0;

	if (nsindex && __le16_to_cpu(nsindex->major) == 1
			&& __le16_to_cpu(nsindex->minor) == 1)
		return nd_set->cookie1;
	return nd_set->cookie2;
}
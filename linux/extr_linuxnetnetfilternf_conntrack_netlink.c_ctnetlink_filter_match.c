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
struct nf_conn {int dummy; } ;
struct ctnetlink_filter {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ctnetlink_filter_match(struct nf_conn *ct, void *data)
{
	struct ctnetlink_filter *filter = data;

	if (filter == NULL)
		return 1;

#ifdef CONFIG_NF_CONNTRACK_MARK
	if ((ct->mark & filter->mark.mask) == filter->mark.val)
		return 1;
#endif

	return 0;
}
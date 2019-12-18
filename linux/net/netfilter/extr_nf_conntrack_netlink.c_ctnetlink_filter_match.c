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
struct nf_conn {int mark; } ;
struct TYPE_2__ {int mask; int val; } ;
struct ctnetlink_filter {scalar_t__ family; TYPE_1__ mark; } ;

/* Variables and functions */
 scalar_t__ nf_ct_l3num (struct nf_conn*) ; 

__attribute__((used)) static int ctnetlink_filter_match(struct nf_conn *ct, void *data)
{
	struct ctnetlink_filter *filter = data;

	if (filter == NULL)
		goto out;

	/* Match entries of a given L3 protocol number.
	 * If it is not specified, ie. l3proto == 0,
	 * then match everything.
	 */
	if (filter->family && nf_ct_l3num(ct) != filter->family)
		goto ignore_entry;

#ifdef CONFIG_NF_CONNTRACK_MARK
	if ((ct->mark & filter->mark.mask) != filter->mark.val)
		goto ignore_entry;
#endif

out:
	return 1;

ignore_entry:
	return 0;
}
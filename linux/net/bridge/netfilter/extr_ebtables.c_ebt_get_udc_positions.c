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
struct ebt_table_info {struct ebt_entries** hook_entry; } ;
struct ebt_entry {scalar_t__ bitmask; } ;
struct ebt_entries {int dummy; } ;
struct TYPE_2__ {scalar_t__ n; struct ebt_entries* chaininfo; } ;
struct ebt_cl_stack {scalar_t__ hookmask; TYPE_1__ cs; } ;

/* Variables and functions */
 int NF_BR_NUMHOOKS ; 

__attribute__((used)) static inline int
ebt_get_udc_positions(struct ebt_entry *e, struct ebt_table_info *newinfo,
		      unsigned int *n, struct ebt_cl_stack *udc)
{
	int i;

	/* we're only interested in chain starts */
	if (e->bitmask)
		return 0;
	for (i = 0; i < NF_BR_NUMHOOKS; i++) {
		if (newinfo->hook_entry[i] == (struct ebt_entries *)e)
			break;
	}
	/* only care about udc */
	if (i != NF_BR_NUMHOOKS)
		return 0;

	udc[*n].cs.chaininfo = (struct ebt_entries *)e;
	/* these initialisations are depended on later in check_chainloops() */
	udc[*n].cs.n = 0;
	udc[*n].hookmask = 0;

	(*n)++;
	return 0;
}
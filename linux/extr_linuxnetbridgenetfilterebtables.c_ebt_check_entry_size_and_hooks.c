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
struct ebt_table_info {scalar_t__* hook_entry; } ;
struct ebt_entry_target {int dummy; } ;
struct ebt_entry {int watchers_offset; int target_offset; int next_offset; int /*<<< orphan*/  bitmask; } ;
struct ebt_entries {scalar_t__ policy; unsigned int counter_offset; unsigned int nentries; } ;

/* Variables and functions */
 scalar_t__ EBT_ACCEPT ; 
 scalar_t__ EBT_DROP ; 
 scalar_t__ EBT_RETURN ; 
 int EINVAL ; 
 int NF_BR_NUMHOOKS ; 

__attribute__((used)) static inline int
ebt_check_entry_size_and_hooks(const struct ebt_entry *e,
			       const struct ebt_table_info *newinfo,
			       unsigned int *n, unsigned int *cnt,
			       unsigned int *totalcnt, unsigned int *udc_cnt)
{
	int i;

	for (i = 0; i < NF_BR_NUMHOOKS; i++) {
		if ((void *)e == (void *)newinfo->hook_entry[i])
			break;
	}
	/* beginning of a new chain
	 * if i == NF_BR_NUMHOOKS it must be a user defined chain
	 */
	if (i != NF_BR_NUMHOOKS || !e->bitmask) {
		/* this checks if the previous chain has as many entries
		 * as it said it has
		 */
		if (*n != *cnt)
			return -EINVAL;

		if (((struct ebt_entries *)e)->policy != EBT_DROP &&
		   ((struct ebt_entries *)e)->policy != EBT_ACCEPT) {
			/* only RETURN from udc */
			if (i != NF_BR_NUMHOOKS ||
			   ((struct ebt_entries *)e)->policy != EBT_RETURN)
				return -EINVAL;
		}
		if (i == NF_BR_NUMHOOKS) /* it's a user defined chain */
			(*udc_cnt)++;
		if (((struct ebt_entries *)e)->counter_offset != *totalcnt)
			return -EINVAL;
		*n = ((struct ebt_entries *)e)->nentries;
		*cnt = 0;
		return 0;
	}
	/* a plain old entry, heh */
	if (sizeof(struct ebt_entry) > e->watchers_offset ||
	   e->watchers_offset > e->target_offset ||
	   e->target_offset >= e->next_offset)
		return -EINVAL;

	/* this is not checked anywhere else */
	if (e->next_offset - e->target_offset < sizeof(struct ebt_entry_target))
		return -EINVAL;

	(*cnt)++;
	(*totalcnt)++;
	return 0;
}
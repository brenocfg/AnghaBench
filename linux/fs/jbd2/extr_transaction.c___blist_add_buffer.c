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
struct journal_head {struct journal_head* b_tprev; struct journal_head* b_tnext; } ;

/* Variables and functions */

__attribute__((used)) static inline void
__blist_add_buffer(struct journal_head **list, struct journal_head *jh)
{
	if (!*list) {
		jh->b_tnext = jh->b_tprev = jh;
		*list = jh;
	} else {
		/* Insert at the tail of the list to preserve order */
		struct journal_head *first = *list, *last = first->b_tprev;
		jh->b_tprev = last;
		jh->b_tnext = first;
		last->b_tnext = first->b_tprev = jh;
	}
}
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
struct j1939_sock {int nfilters; struct j1939_filter* filters; } ;
struct TYPE_2__ {int pgn; int sa; int src_name; } ;
struct j1939_sk_buff_cb {TYPE_1__ addr; } ;
struct j1939_filter {int pgn_mask; int pgn; int addr_mask; int addr; int name_mask; int name; } ;

/* Variables and functions */

__attribute__((used)) static bool j1939_sk_match_filter(struct j1939_sock *jsk,
				  const struct j1939_sk_buff_cb *skcb)
{
	const struct j1939_filter *f = jsk->filters;
	int nfilter = jsk->nfilters;

	if (!nfilter)
		/* receive all when no filters are assigned */
		return true;

	for (; nfilter; ++f, --nfilter) {
		if ((skcb->addr.pgn & f->pgn_mask) != f->pgn)
			continue;
		if ((skcb->addr.sa & f->addr_mask) != f->addr)
			continue;
		if ((skcb->addr.src_name & f->name_mask) != f->name)
			continue;
		return true;
	}
	return false;
}
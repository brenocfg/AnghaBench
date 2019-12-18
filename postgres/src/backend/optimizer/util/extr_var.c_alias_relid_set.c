#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rtable; } ;
struct TYPE_6__ {scalar_t__ rtekind; } ;
typedef  int /*<<< orphan*/ * Relids ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  TYPE_2__ Query ;

/* Variables and functions */
 scalar_t__ RTE_JOIN ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * bms_join (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_relids_for_join (TYPE_2__*,int) ; 
 TYPE_1__* rt_fetch (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Relids
alias_relid_set(Query *query, Relids relids)
{
	Relids		result = NULL;
	int			rtindex;

	rtindex = -1;
	while ((rtindex = bms_next_member(relids, rtindex)) >= 0)
	{
		RangeTblEntry *rte = rt_fetch(rtindex, query->rtable);

		if (rte->rtekind == RTE_JOIN)
			result = bms_join(result, get_relids_for_join(query, rtindex));
		else
			result = bms_add_member(result, rtindex);
	}
	return result;
}
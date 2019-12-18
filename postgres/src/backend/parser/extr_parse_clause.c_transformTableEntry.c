#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  inh; int /*<<< orphan*/  alias; } ;
typedef  TYPE_1__ RangeVar ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  int /*<<< orphan*/  ParseState ;

/* Variables and functions */
 int /*<<< orphan*/ * addRangeTableEntry (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static RangeTblEntry *
transformTableEntry(ParseState *pstate, RangeVar *r)
{
	RangeTblEntry *rte;

	/* We need only build a range table entry */
	rte = addRangeTableEntry(pstate, r, r->alias, r->inh, true);

	return rte;
}
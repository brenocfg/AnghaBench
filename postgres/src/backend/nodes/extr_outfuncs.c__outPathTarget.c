#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  per_tuple; int /*<<< orphan*/  startup; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sortgrouprefs; int /*<<< orphan*/  exprs; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ PathTarget ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ cost ; 
 int /*<<< orphan*/  exprs ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  width ; 

__attribute__((used)) static void
_outPathTarget(StringInfo str, const PathTarget *node)
{
	WRITE_NODE_TYPE("PATHTARGET");

	WRITE_NODE_FIELD(exprs);
	if (node->sortgrouprefs)
	{
		int			i;

		appendStringInfoString(str, " :sortgrouprefs");
		for (i = 0; i < list_length(node->exprs); i++)
			appendStringInfo(str, " %u", node->sortgrouprefs[i]);
	}
	WRITE_FLOAT_FIELD(cost.startup, "%.2f");
	WRITE_FLOAT_FIELD(cost.per_tuple, "%.2f");
	WRITE_INT_FIELD(width);
}
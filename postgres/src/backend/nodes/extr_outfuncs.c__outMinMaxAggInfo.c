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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  MinMaxAggInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aggfnoid ; 
 int /*<<< orphan*/  aggsortop ; 
 int /*<<< orphan*/  param ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  pathcost ; 
 int /*<<< orphan*/  target ; 

__attribute__((used)) static void
_outMinMaxAggInfo(StringInfo str, const MinMaxAggInfo *node)
{
	WRITE_NODE_TYPE("MINMAXAGGINFO");

	WRITE_OID_FIELD(aggfnoid);
	WRITE_OID_FIELD(aggsortop);
	WRITE_NODE_FIELD(target);
	/* We intentionally omit subroot --- too large, not interesting enough */
	WRITE_NODE_FIELD(path);
	WRITE_FLOAT_FIELD(pathcost, "%.2f");
	WRITE_NODE_FIELD(param);
}
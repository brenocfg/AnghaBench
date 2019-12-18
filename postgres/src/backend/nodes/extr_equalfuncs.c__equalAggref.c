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
typedef  int /*<<< orphan*/  Aggref ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aggargtypes ; 
 int /*<<< orphan*/  aggcollid ; 
 int /*<<< orphan*/  aggdirectargs ; 
 int /*<<< orphan*/  aggdistinct ; 
 int /*<<< orphan*/  aggfilter ; 
 int /*<<< orphan*/  aggfnoid ; 
 int /*<<< orphan*/  aggkind ; 
 int /*<<< orphan*/  agglevelsup ; 
 int /*<<< orphan*/  aggorder ; 
 int /*<<< orphan*/  aggsplit ; 
 int /*<<< orphan*/  aggstar ; 
 int /*<<< orphan*/  aggtype ; 
 int /*<<< orphan*/  aggvariadic ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  inputcollid ; 
 int /*<<< orphan*/  location ; 

__attribute__((used)) static bool
_equalAggref(const Aggref *a, const Aggref *b)
{
	COMPARE_SCALAR_FIELD(aggfnoid);
	COMPARE_SCALAR_FIELD(aggtype);
	COMPARE_SCALAR_FIELD(aggcollid);
	COMPARE_SCALAR_FIELD(inputcollid);
	/* ignore aggtranstype since it might not be set yet */
	COMPARE_NODE_FIELD(aggargtypes);
	COMPARE_NODE_FIELD(aggdirectargs);
	COMPARE_NODE_FIELD(args);
	COMPARE_NODE_FIELD(aggorder);
	COMPARE_NODE_FIELD(aggdistinct);
	COMPARE_NODE_FIELD(aggfilter);
	COMPARE_SCALAR_FIELD(aggstar);
	COMPARE_SCALAR_FIELD(aggvariadic);
	COMPARE_SCALAR_FIELD(aggkind);
	COMPARE_SCALAR_FIELD(agglevelsup);
	COMPARE_SCALAR_FIELD(aggsplit);
	COMPARE_LOCATION_FIELD(location);

	return true;
}
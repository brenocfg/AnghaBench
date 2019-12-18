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
typedef  int /*<<< orphan*/  Aggref ;

/* Variables and functions */
 int /*<<< orphan*/  AggSplit ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_CHAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  aggtranstype ; 
 int /*<<< orphan*/  aggtype ; 
 int /*<<< orphan*/  aggvariadic ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  inputcollid ; 
 int /*<<< orphan*/  location ; 

__attribute__((used)) static void
_outAggref(StringInfo str, const Aggref *node)
{
	WRITE_NODE_TYPE("AGGREF");

	WRITE_OID_FIELD(aggfnoid);
	WRITE_OID_FIELD(aggtype);
	WRITE_OID_FIELD(aggcollid);
	WRITE_OID_FIELD(inputcollid);
	WRITE_OID_FIELD(aggtranstype);
	WRITE_NODE_FIELD(aggargtypes);
	WRITE_NODE_FIELD(aggdirectargs);
	WRITE_NODE_FIELD(args);
	WRITE_NODE_FIELD(aggorder);
	WRITE_NODE_FIELD(aggdistinct);
	WRITE_NODE_FIELD(aggfilter);
	WRITE_BOOL_FIELD(aggstar);
	WRITE_BOOL_FIELD(aggvariadic);
	WRITE_CHAR_FIELD(aggkind);
	WRITE_UINT_FIELD(agglevelsup);
	WRITE_ENUM_FIELD(aggsplit, AggSplit);
	WRITE_LOCATION_FIELD(location);
}
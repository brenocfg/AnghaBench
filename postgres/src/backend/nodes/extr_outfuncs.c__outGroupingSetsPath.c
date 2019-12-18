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
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  GroupingSetsPath ;

/* Variables and functions */
 int /*<<< orphan*/  AggStrategy ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  _outPathInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  aggstrategy ; 
 int /*<<< orphan*/  qual ; 
 int /*<<< orphan*/  rollups ; 
 int /*<<< orphan*/  subpath ; 

__attribute__((used)) static void
_outGroupingSetsPath(StringInfo str, const GroupingSetsPath *node)
{
	WRITE_NODE_TYPE("GROUPINGSETSPATH");

	_outPathInfo(str, (const Path *) node);

	WRITE_NODE_FIELD(subpath);
	WRITE_ENUM_FIELD(aggstrategy, AggStrategy);
	WRITE_NODE_FIELD(rollups);
	WRITE_NODE_FIELD(qual);
}
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
typedef  int /*<<< orphan*/  Join ;
typedef  int /*<<< orphan*/  HashJoin ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  _outJoinPlanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hashclauses ; 
 int /*<<< orphan*/  hashcollations ; 
 int /*<<< orphan*/  hashkeys ; 
 int /*<<< orphan*/  hashoperators ; 

__attribute__((used)) static void
_outHashJoin(StringInfo str, const HashJoin *node)
{
	WRITE_NODE_TYPE("HASHJOIN");

	_outJoinPlanInfo(str, (const Join *) node);

	WRITE_NODE_FIELD(hashclauses);
	WRITE_NODE_FIELD(hashoperators);
	WRITE_NODE_FIELD(hashcollations);
	WRITE_NODE_FIELD(hashkeys);
}
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
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Join ;

/* Variables and functions */
 int /*<<< orphan*/  JoinType ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outPlanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  inner_unique ; 
 int /*<<< orphan*/  joinqual ; 
 int /*<<< orphan*/  jointype ; 

__attribute__((used)) static void
_outJoinPlanInfo(StringInfo str, const Join *node)
{
	_outPlanInfo(str, (const Plan *) node);

	WRITE_ENUM_FIELD(jointype, JoinType);
	WRITE_BOOL_FIELD(inner_unique);
	WRITE_NODE_FIELD(joinqual);
}
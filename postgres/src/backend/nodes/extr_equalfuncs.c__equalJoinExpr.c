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
typedef  int /*<<< orphan*/  JoinExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alias ; 
 int /*<<< orphan*/  isNatural ; 
 int /*<<< orphan*/  jointype ; 
 int /*<<< orphan*/  larg ; 
 int /*<<< orphan*/  quals ; 
 int /*<<< orphan*/  rarg ; 
 int /*<<< orphan*/  rtindex ; 
 int /*<<< orphan*/  usingClause ; 

__attribute__((used)) static bool
_equalJoinExpr(const JoinExpr *a, const JoinExpr *b)
{
	COMPARE_SCALAR_FIELD(jointype);
	COMPARE_SCALAR_FIELD(isNatural);
	COMPARE_NODE_FIELD(larg);
	COMPARE_NODE_FIELD(rarg);
	COMPARE_NODE_FIELD(usingClause);
	COMPARE_NODE_FIELD(quals);
	COMPARE_NODE_FIELD(alias);
	COMPARE_SCALAR_FIELD(rtindex);

	return true;
}
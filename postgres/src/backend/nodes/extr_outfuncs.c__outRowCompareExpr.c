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
typedef  int /*<<< orphan*/  RowCompareExpr ;

/* Variables and functions */
 int /*<<< orphan*/  RowCompareType ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  inputcollids ; 
 int /*<<< orphan*/  largs ; 
 int /*<<< orphan*/  opfamilies ; 
 int /*<<< orphan*/  opnos ; 
 int /*<<< orphan*/  rargs ; 
 int /*<<< orphan*/  rctype ; 

__attribute__((used)) static void
_outRowCompareExpr(StringInfo str, const RowCompareExpr *node)
{
	WRITE_NODE_TYPE("ROWCOMPARE");

	WRITE_ENUM_FIELD(rctype, RowCompareType);
	WRITE_NODE_FIELD(opnos);
	WRITE_NODE_FIELD(opfamilies);
	WRITE_NODE_FIELD(inputcollids);
	WRITE_NODE_FIELD(largs);
	WRITE_NODE_FIELD(rargs);
}
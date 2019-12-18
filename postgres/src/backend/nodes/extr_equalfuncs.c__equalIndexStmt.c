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
typedef  int /*<<< orphan*/  IndexStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accessMethod ; 
 int /*<<< orphan*/  concurrent ; 
 int /*<<< orphan*/  deferrable ; 
 int /*<<< orphan*/  excludeOpNames ; 
 int /*<<< orphan*/  idxcomment ; 
 int /*<<< orphan*/  idxname ; 
 int /*<<< orphan*/  if_not_exists ; 
 int /*<<< orphan*/  indexIncludingParams ; 
 int /*<<< orphan*/  indexOid ; 
 int /*<<< orphan*/  indexParams ; 
 int /*<<< orphan*/  initdeferred ; 
 int /*<<< orphan*/  isconstraint ; 
 int /*<<< orphan*/  oldNode ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  primary ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  reset_default_tblspc ; 
 int /*<<< orphan*/  tableSpace ; 
 int /*<<< orphan*/  transformed ; 
 int /*<<< orphan*/  unique ; 
 int /*<<< orphan*/  whereClause ; 

__attribute__((used)) static bool
_equalIndexStmt(const IndexStmt *a, const IndexStmt *b)
{
	COMPARE_STRING_FIELD(idxname);
	COMPARE_NODE_FIELD(relation);
	COMPARE_STRING_FIELD(accessMethod);
	COMPARE_STRING_FIELD(tableSpace);
	COMPARE_NODE_FIELD(indexParams);
	COMPARE_NODE_FIELD(indexIncludingParams);
	COMPARE_NODE_FIELD(options);
	COMPARE_NODE_FIELD(whereClause);
	COMPARE_NODE_FIELD(excludeOpNames);
	COMPARE_STRING_FIELD(idxcomment);
	COMPARE_SCALAR_FIELD(indexOid);
	COMPARE_SCALAR_FIELD(oldNode);
	COMPARE_SCALAR_FIELD(unique);
	COMPARE_SCALAR_FIELD(primary);
	COMPARE_SCALAR_FIELD(isconstraint);
	COMPARE_SCALAR_FIELD(deferrable);
	COMPARE_SCALAR_FIELD(initdeferred);
	COMPARE_SCALAR_FIELD(transformed);
	COMPARE_SCALAR_FIELD(concurrent);
	COMPARE_SCALAR_FIELD(if_not_exists);
	COMPARE_SCALAR_FIELD(reset_default_tblspc);

	return true;
}
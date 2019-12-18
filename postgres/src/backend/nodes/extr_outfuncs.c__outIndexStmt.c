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
typedef  int /*<<< orphan*/  IndexStmt ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
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

__attribute__((used)) static void
_outIndexStmt(StringInfo str, const IndexStmt *node)
{
	WRITE_NODE_TYPE("INDEXSTMT");

	WRITE_STRING_FIELD(idxname);
	WRITE_NODE_FIELD(relation);
	WRITE_STRING_FIELD(accessMethod);
	WRITE_STRING_FIELD(tableSpace);
	WRITE_NODE_FIELD(indexParams);
	WRITE_NODE_FIELD(indexIncludingParams);
	WRITE_NODE_FIELD(options);
	WRITE_NODE_FIELD(whereClause);
	WRITE_NODE_FIELD(excludeOpNames);
	WRITE_STRING_FIELD(idxcomment);
	WRITE_OID_FIELD(indexOid);
	WRITE_OID_FIELD(oldNode);
	WRITE_BOOL_FIELD(unique);
	WRITE_BOOL_FIELD(primary);
	WRITE_BOOL_FIELD(isconstraint);
	WRITE_BOOL_FIELD(deferrable);
	WRITE_BOOL_FIELD(initdeferred);
	WRITE_BOOL_FIELD(transformed);
	WRITE_BOOL_FIELD(concurrent);
	WRITE_BOOL_FIELD(if_not_exists);
	WRITE_BOOL_FIELD(reset_default_tblspc);
}
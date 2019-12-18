#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  attnotnull; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  AlteredTableInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TABLE_DEFINITION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheAttName (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 

__attribute__((used)) static void
ATExecCheckNotNull(AlteredTableInfo *tab, Relation rel,
				   const char *colName, LOCKMODE lockmode)
{
	HeapTuple	tuple;

	tuple = SearchSysCacheAttName(RelationGetRelid(rel), colName);

	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_COLUMN),
				 errmsg("column \"%s\" of relation \"%s\" does not exist",
						colName, RelationGetRelationName(rel))));

	if (!((Form_pg_attribute) GETSTRUCT(tuple))->attnotnull)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
				 errmsg("constraint must be added to child tables too"),
				 errdetail("Column \"%s\" of relation \"%s\" is not already NOT NULL.",
						   colName, RelationGetRelationName(rel)),
				 errhint("Do not specify the ONLY keyword.")));

	ReleaseSysCache(tuple);
}
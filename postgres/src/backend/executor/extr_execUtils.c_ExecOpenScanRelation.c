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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int EXEC_FLAG_EXPLAIN_ONLY ; 
 int EXEC_FLAG_WITH_NO_DATA ; 
 int /*<<< orphan*/  ExecGetRangeTableRelation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationIsScannable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

Relation
ExecOpenScanRelation(EState *estate, Index scanrelid, int eflags)
{
	Relation	rel;

	/* Open the relation. */
	rel = ExecGetRangeTableRelation(estate, scanrelid);

	/*
	 * Complain if we're attempting a scan of an unscannable relation, except
	 * when the query won't actually be run.  This is a slightly klugy place
	 * to do this, perhaps, but there is no better place.
	 */
	if ((eflags & (EXEC_FLAG_EXPLAIN_ONLY | EXEC_FLAG_WITH_NO_DATA)) == 0 &&
		!RelationIsScannable(rel))
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("materialized view \"%s\" has not been populated",
						RelationGetRelationName(rel)),
				 errhint("Use the REFRESH MATERIALIZED VIEW command.")));

	return rel;
}
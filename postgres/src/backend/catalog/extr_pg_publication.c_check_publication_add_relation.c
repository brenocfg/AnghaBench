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
struct TYPE_2__ {scalar_t__ relkind; } ;
typedef  int /*<<< orphan*/  Relation ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsCatalogRelation (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 TYPE_1__* RelationGetForm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_publication_add_relation(Relation targetrel)
{
	/* Give more specific error for partitioned tables */
	if (RelationGetForm(targetrel)->relkind == RELKIND_PARTITIONED_TABLE)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("\"%s\" is a partitioned table",
						RelationGetRelationName(targetrel)),
				 errdetail("Adding partitioned tables to publications is not supported."),
				 errhint("You can add the table partitions individually.")));

	/* Must be table */
	if (RelationGetForm(targetrel)->relkind != RELKIND_RELATION)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("\"%s\" is not a table",
						RelationGetRelationName(targetrel)),
				 errdetail("Only tables can be added to publications.")));

	/* Can't be system table */
	if (IsCatalogRelation(targetrel))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("\"%s\" is a system table",
						RelationGetRelationName(targetrel)),
				 errdetail("System tables cannot be added to publications.")));

	/* UNLOGGED and TEMP relations cannot be part of publication. */
	if (!RelationNeedsWAL(targetrel))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("table \"%s\" cannot be replicated",
						RelationGetRelationName(targetrel)),
				 errdetail("Temporary and unlogged relations cannot be replicated.")));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int rd_refcnt; TYPE_1__* rd_rel; scalar_t__ rd_isnailed; } ;
struct TYPE_6__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 scalar_t__ AfterTriggerPendingOnRel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_IN_USE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ RELKIND_INDEX ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 

void
CheckTableNotInUse(Relation rel, const char *stmt)
{
	int			expected_refcnt;

	expected_refcnt = rel->rd_isnailed ? 2 : 1;
	if (rel->rd_refcnt != expected_refcnt)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_IN_USE),
		/* translator: first %s is a SQL command, eg ALTER TABLE */
				 errmsg("cannot %s \"%s\" because it is being used by active queries in this session",
						stmt, RelationGetRelationName(rel))));

	if (rel->rd_rel->relkind != RELKIND_INDEX &&
		rel->rd_rel->relkind != RELKIND_PARTITIONED_INDEX &&
		AfterTriggerPendingOnRel(RelationGetRelid(rel)))
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_IN_USE),
		/* translator: first %s is a SQL command, eg ALTER TABLE */
				 errmsg("cannot %s \"%s\" because it has pending trigger events",
						stmt, RelationGetRelationName(rel))));
}
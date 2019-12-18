#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  pstate; int /*<<< orphan*/  partbound; TYPE_2__* rel; } ;
struct TYPE_12__ {int /*<<< orphan*/ * bound; } ;
struct TYPE_11__ {TYPE_1__* rd_rel; } ;
struct TYPE_10__ {int relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__ PartitionCmd ;
typedef  TYPE_4__ CreateStmtContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
#define  RELKIND_INDEX 131 
#define  RELKIND_PARTITIONED_INDEX 130 
#define  RELKIND_PARTITIONED_TABLE 129 
#define  RELKIND_RELATION 128 
 int /*<<< orphan*/ * RelationGetPartitionKey (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transformPartitionBound (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
transformPartitionCmd(CreateStmtContext *cxt, PartitionCmd *cmd)
{
	Relation	parentRel = cxt->rel;

	switch (parentRel->rd_rel->relkind)
	{
		case RELKIND_PARTITIONED_TABLE:
			/* transform the partition bound, if any */
			Assert(RelationGetPartitionKey(parentRel) != NULL);
			if (cmd->bound != NULL)
				cxt->partbound = transformPartitionBound(cxt->pstate, parentRel,
														 cmd->bound);
			break;
		case RELKIND_PARTITIONED_INDEX:
			/* nothing to check */
			Assert(cmd->bound == NULL);
			break;
		case RELKIND_RELATION:
			/* the table must be partitioned */
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("table \"%s\" is not partitioned",
							RelationGetRelationName(parentRel))));
			break;
		case RELKIND_INDEX:
			/* the index must be partitioned */
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("index \"%s\" is not partitioned",
							RelationGetRelationName(parentRel))));
			break;
		default:
			/* parser shouldn't let this case through */
			elog(ERROR, "\"%s\" is not a partitioned table or index",
				 RelationGetRelationName(parentRel));
			break;
	}
}
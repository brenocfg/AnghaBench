#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* rd_rel; } ;
struct TYPE_8__ {int relkind; } ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int ATT_COMPOSITE_TYPE ; 
 int ATT_FOREIGN_TABLE ; 
 int ATT_INDEX ; 
 int ATT_MATVIEW ; 
 int ATT_PARTITIONED_INDEX ; 
 int ATT_TABLE ; 
 int ATT_VIEW ; 
 int /*<<< orphan*/  ATWrongRelkindError (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 scalar_t__ IsSystemRelation (TYPE_2__*) ; 
#define  RELKIND_COMPOSITE_TYPE 135 
#define  RELKIND_FOREIGN_TABLE 134 
#define  RELKIND_INDEX 133 
#define  RELKIND_MATVIEW 132 
#define  RELKIND_PARTITIONED_INDEX 131 
#define  RELKIND_PARTITIONED_TABLE 130 
#define  RELKIND_RELATION 129 
#define  RELKIND_VIEW 128 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allowSystemTableMods ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relkind_objtype (int) ; 
 int /*<<< orphan*/  pg_class_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ATSimplePermissions(Relation rel, int allowed_targets)
{
	int			actual_target;

	switch (rel->rd_rel->relkind)
	{
		case RELKIND_RELATION:
		case RELKIND_PARTITIONED_TABLE:
			actual_target = ATT_TABLE;
			break;
		case RELKIND_VIEW:
			actual_target = ATT_VIEW;
			break;
		case RELKIND_MATVIEW:
			actual_target = ATT_MATVIEW;
			break;
		case RELKIND_INDEX:
			actual_target = ATT_INDEX;
			break;
		case RELKIND_PARTITIONED_INDEX:
			actual_target = ATT_PARTITIONED_INDEX;
			break;
		case RELKIND_COMPOSITE_TYPE:
			actual_target = ATT_COMPOSITE_TYPE;
			break;
		case RELKIND_FOREIGN_TABLE:
			actual_target = ATT_FOREIGN_TABLE;
			break;
		default:
			actual_target = 0;
			break;
	}

	/* Wrong target type? */
	if ((actual_target & allowed_targets) == 0)
		ATWrongRelkindError(rel, allowed_targets);

	/* Permissions checks */
	if (!pg_class_ownercheck(RelationGetRelid(rel), GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, get_relkind_objtype(rel->rd_rel->relkind),
					   RelationGetRelationName(rel));

	if (!allowSystemTableMods && IsSystemRelation(rel))
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied: \"%s\" is a system catalog",
						RelationGetRelationName(rel))));
}
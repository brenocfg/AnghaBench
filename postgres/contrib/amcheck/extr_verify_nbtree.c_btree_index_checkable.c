#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* rd_index; TYPE_2__* rd_rel; } ;
struct TYPE_8__ {scalar_t__ relkind; scalar_t__ relam; } ;
struct TYPE_7__ {int /*<<< orphan*/  indisvalid; } ;
typedef  TYPE_3__* Relation ;

/* Variables and functions */
 scalar_t__ BTREE_AM_OID ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ RELATION_IS_OTHER_TEMP (TYPE_3__*) ; 
 scalar_t__ RELKIND_INDEX ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 

__attribute__((used)) static inline void
btree_index_checkable(Relation rel)
{
	if (rel->rd_rel->relkind != RELKIND_INDEX ||
		rel->rd_rel->relam != BTREE_AM_OID)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("only B-Tree indexes are supported as targets for verification"),
				 errdetail("Relation \"%s\" is not a B-Tree index.",
						   RelationGetRelationName(rel))));

	if (RELATION_IS_OTHER_TEMP(rel))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot access temporary tables of other sessions"),
				 errdetail("Index \"%s\" is associated with temporary relation.",
						   RelationGetRelationName(rel))));

	if (!rel->rd_index->indisvalid)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot check index \"%s\"",
						RelationGetRelationName(rel)),
				 errdetail("Index is not valid.")));
}
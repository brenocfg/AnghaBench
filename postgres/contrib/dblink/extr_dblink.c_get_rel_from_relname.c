#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_8__ {TYPE_1__* rd_rel; } ;
struct TYPE_7__ {int /*<<< orphan*/  relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  scalar_t__ AclResult ;
typedef  int /*<<< orphan*/  AclMode ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relkind_objtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeRangeVarFromNameList (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_class_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_openrv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textToQualifiedNameList (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Relation
get_rel_from_relname(text *relname_text, LOCKMODE lockmode, AclMode aclmode)
{
	RangeVar   *relvar;
	Relation	rel;
	AclResult	aclresult;

	relvar = makeRangeVarFromNameList(textToQualifiedNameList(relname_text));
	rel = table_openrv(relvar, lockmode);

	aclresult = pg_class_aclcheck(RelationGetRelid(rel), GetUserId(),
								  aclmode);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, get_relkind_objtype(rel->rd_rel->relkind),
					   RelationGetRelationName(rel));

	return rel;
}
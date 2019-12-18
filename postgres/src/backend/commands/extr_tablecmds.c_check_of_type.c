#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ typtype; int /*<<< orphan*/  oid; int /*<<< orphan*/  typrelid; } ;
struct TYPE_7__ {TYPE_1__* rd_rel; } ;
struct TYPE_6__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_COMPOSITE_TYPE ; 
 scalar_t__ TYPTYPE_COMPOSITE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
check_of_type(HeapTuple typetuple)
{
	Form_pg_type typ = (Form_pg_type) GETSTRUCT(typetuple);
	bool		typeOk = false;

	if (typ->typtype == TYPTYPE_COMPOSITE)
	{
		Relation	typeRelation;

		Assert(OidIsValid(typ->typrelid));
		typeRelation = relation_open(typ->typrelid, AccessShareLock);
		typeOk = (typeRelation->rd_rel->relkind == RELKIND_COMPOSITE_TYPE);

		/*
		 * Close the parent rel, but keep our AccessShareLock on it until xact
		 * commit.  That will prevent someone else from deleting or ALTERing
		 * the type before the typed table creation/conversion commits.
		 */
		relation_close(typeRelation, NoLock);
	}
	if (!typeOk)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("type %s is not a composite type",
						format_type_be(typ->oid))));
}
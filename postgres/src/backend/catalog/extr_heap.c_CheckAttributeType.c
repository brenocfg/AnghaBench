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
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {scalar_t__ atttypid; scalar_t__ attcollation; int /*<<< orphan*/  attname; scalar_t__ attisdropped; } ;
struct TYPE_6__ {int natts; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__* Form_pg_attribute ;

/* Variables and functions */
 scalar_t__ ANYARRAYOID ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int CHKATYPE_ANYARRAY ; 
 int CHKATYPE_ANYRECORD ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TABLE_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ RECORDARRAYOID ; 
 scalar_t__ RECORDOID ; 
 TYPE_1__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 char TYPTYPE_COMPOSITE ; 
 char TYPTYPE_DOMAIN ; 
 char TYPTYPE_PSEUDO ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ getBaseType (scalar_t__) ; 
 scalar_t__ get_element_type (scalar_t__) ; 
 int /*<<< orphan*/  get_typ_typrelid (scalar_t__) ; 
 char get_typtype (scalar_t__) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * list_delete_last (int /*<<< orphan*/ *) ; 
 scalar_t__ list_member_oid (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ type_is_collatable (scalar_t__) ; 

void
CheckAttributeType(const char *attname,
				   Oid atttypid, Oid attcollation,
				   List *containing_rowtypes,
				   int flags)
{
	char		att_typtype = get_typtype(atttypid);
	Oid			att_typelem;

	if (att_typtype == TYPTYPE_PSEUDO)
	{
		/*
		 * We disallow pseudo-type columns, with the exception of ANYARRAY,
		 * RECORD, and RECORD[] when the caller says that those are OK.
		 *
		 * We don't need to worry about recursive containment for RECORD and
		 * RECORD[] because (a) no named composite type should be allowed to
		 * contain those, and (b) two "anonymous" record types couldn't be
		 * considered to be the same type, so infinite recursion isn't
		 * possible.
		 */
		if (!((atttypid == ANYARRAYOID && (flags & CHKATYPE_ANYARRAY)) ||
			  (atttypid == RECORDOID && (flags & CHKATYPE_ANYRECORD)) ||
			  (atttypid == RECORDARRAYOID && (flags & CHKATYPE_ANYRECORD))))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
					 errmsg("column \"%s\" has pseudo-type %s",
							attname, format_type_be(atttypid))));
	}
	else if (att_typtype == TYPTYPE_DOMAIN)
	{
		/*
		 * If it's a domain, recurse to check its base type.
		 */
		CheckAttributeType(attname, getBaseType(atttypid), attcollation,
						   containing_rowtypes,
						   flags);
	}
	else if (att_typtype == TYPTYPE_COMPOSITE)
	{
		/*
		 * For a composite type, recurse into its attributes.
		 */
		Relation	relation;
		TupleDesc	tupdesc;
		int			i;

		/*
		 * Check for self-containment.  Eventually we might be able to allow
		 * this (just return without complaint, if so) but it's not clear how
		 * many other places would require anti-recursion defenses before it
		 * would be safe to allow tables to contain their own rowtype.
		 */
		if (list_member_oid(containing_rowtypes, atttypid))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
					 errmsg("composite type %s cannot be made a member of itself",
							format_type_be(atttypid))));

		containing_rowtypes = lappend_oid(containing_rowtypes, atttypid);

		relation = relation_open(get_typ_typrelid(atttypid), AccessShareLock);

		tupdesc = RelationGetDescr(relation);

		for (i = 0; i < tupdesc->natts; i++)
		{
			Form_pg_attribute attr = TupleDescAttr(tupdesc, i);

			if (attr->attisdropped)
				continue;
			CheckAttributeType(NameStr(attr->attname),
							   attr->atttypid, attr->attcollation,
							   containing_rowtypes,
							   flags);
		}

		relation_close(relation, AccessShareLock);

		containing_rowtypes = list_delete_last(containing_rowtypes);
	}
	else if (OidIsValid((att_typelem = get_element_type(atttypid))))
	{
		/*
		 * Must recurse into array types, too, in case they are composite.
		 */
		CheckAttributeType(attname, att_typelem, attcollation,
						   containing_rowtypes,
						   flags);
	}

	/*
	 * This might not be strictly invalid per SQL standard, but it is pretty
	 * useless, and it cannot be dumped, so we must disallow it.
	 */
	if (!OidIsValid(attcollation) && type_is_collatable(atttypid))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
				 errmsg("no collation was derived for column \"%s\" with collatable type %s",
						attname, format_type_be(atttypid)),
				 errhint("Use the COLLATE clause to set the collation explicitly.")));
}
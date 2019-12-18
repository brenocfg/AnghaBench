#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__* values; } ;
struct TYPE_15__ {scalar_t__ indrelid; scalar_t__ indexrelid; TYPE_1__ indkey; } ;
struct TYPE_14__ {int /*<<< orphan*/ * rd_opcintype; TYPE_4__* rd_index; } ;
struct TYPE_13__ {char* data; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  TYPE_3__* Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_4__* Form_pg_index ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ AttrNumber ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_SELECT ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int IndexRelationGetNumberOfKeyAttributes (TYPE_3__*) ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 char* OidOutputFunctionCall (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ RLS_ENABLED ; 
 scalar_t__ RelationGetRelid (TYPE_3__*) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_2__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_2__*,char*) ; 
 scalar_t__ check_enable_rls (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 scalar_t__ pg_attribute_aclcheck (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_class_aclcheck (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_get_indexdef_columns (scalar_t__,int) ; 

char *
BuildIndexValueDescription(Relation indexRelation,
						   Datum *values, bool *isnull)
{
	StringInfoData buf;
	Form_pg_index idxrec;
	int			indnkeyatts;
	int			i;
	int			keyno;
	Oid			indexrelid = RelationGetRelid(indexRelation);
	Oid			indrelid;
	AclResult	aclresult;

	indnkeyatts = IndexRelationGetNumberOfKeyAttributes(indexRelation);

	/*
	 * Check permissions- if the user does not have access to view all of the
	 * key columns then return NULL to avoid leaking data.
	 *
	 * First check if RLS is enabled for the relation.  If so, return NULL to
	 * avoid leaking data.
	 *
	 * Next we need to check table-level SELECT access and then, if there is
	 * no access there, check column-level permissions.
	 */
	idxrec = indexRelation->rd_index;
	indrelid = idxrec->indrelid;
	Assert(indexrelid == idxrec->indexrelid);

	/* RLS check- if RLS is enabled then we don't return anything. */
	if (check_enable_rls(indrelid, InvalidOid, true) == RLS_ENABLED)
		return NULL;

	/* Table-level SELECT is enough, if the user has it */
	aclresult = pg_class_aclcheck(indrelid, GetUserId(), ACL_SELECT);
	if (aclresult != ACLCHECK_OK)
	{
		/*
		 * No table-level access, so step through the columns in the index and
		 * make sure the user has SELECT rights on all of them.
		 */
		for (keyno = 0; keyno < indnkeyatts; keyno++)
		{
			AttrNumber	attnum = idxrec->indkey.values[keyno];

			/*
			 * Note that if attnum == InvalidAttrNumber, then this is an index
			 * based on an expression and we return no detail rather than try
			 * to figure out what column(s) the expression includes and if the
			 * user has SELECT rights on them.
			 */
			if (attnum == InvalidAttrNumber ||
				pg_attribute_aclcheck(indrelid, attnum, GetUserId(),
									  ACL_SELECT) != ACLCHECK_OK)
			{
				/* No access, so clean up and return */
				return NULL;
			}
		}
	}

	initStringInfo(&buf);
	appendStringInfo(&buf, "(%s)=(",
					 pg_get_indexdef_columns(indexrelid, true));

	for (i = 0; i < indnkeyatts; i++)
	{
		char	   *val;

		if (isnull[i])
			val = "null";
		else
		{
			Oid			foutoid;
			bool		typisvarlena;

			/*
			 * The provided data is not necessarily of the type stored in the
			 * index; rather it is of the index opclass's input type. So look
			 * at rd_opcintype not the index tupdesc.
			 *
			 * Note: this is a bit shaky for opclasses that have pseudotype
			 * input types such as ANYARRAY or RECORD.  Currently, the
			 * typoutput functions associated with the pseudotypes will work
			 * okay, but we might have to try harder in future.
			 */
			getTypeOutputInfo(indexRelation->rd_opcintype[i],
							  &foutoid, &typisvarlena);
			val = OidOutputFunctionCall(foutoid, values[i]);
		}

		if (i > 0)
			appendStringInfoString(&buf, ", ");
		appendStringInfoString(&buf, val);
	}

	appendStringInfoChar(&buf, ')');

	return buf.data;
}
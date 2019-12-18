#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * tts_values; scalar_t__* tts_isnull; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_17__ {int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; scalar_t__ attnum; scalar_t__ attisdropped; } ;
struct TYPE_16__ {char* data; int len; } ;
struct TYPE_15__ {int natts; } ;
typedef  TYPE_3__ StringInfoData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_SELECT ; 
 scalar_t__ FirstLowInvalidHeapAttributeNumber ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvalidOid ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RLS_ENABLED ; 
 TYPE_4__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  appendBinaryStringInfo (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_3__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_3__*,char*) ; 
 scalar_t__ bms_is_member (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ check_enable_rls (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_3__*) ; 
 scalar_t__ pg_attribute_aclcheck (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_class_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pg_mbcliplen (char*,int,int) ; 
 int /*<<< orphan*/  slot_getallattrs (TYPE_1__*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
ExecBuildSlotValueDescription(Oid reloid,
							  TupleTableSlot *slot,
							  TupleDesc tupdesc,
							  Bitmapset *modifiedCols,
							  int maxfieldlen)
{
	StringInfoData buf;
	StringInfoData collist;
	bool		write_comma = false;
	bool		write_comma_collist = false;
	int			i;
	AclResult	aclresult;
	bool		table_perm = false;
	bool		any_perm = false;

	/*
	 * Check if RLS is enabled and should be active for the relation; if so,
	 * then don't return anything.  Otherwise, go through normal permission
	 * checks.
	 */
	if (check_enable_rls(reloid, InvalidOid, true) == RLS_ENABLED)
		return NULL;

	initStringInfo(&buf);

	appendStringInfoChar(&buf, '(');

	/*
	 * Check if the user has permissions to see the row.  Table-level SELECT
	 * allows access to all columns.  If the user does not have table-level
	 * SELECT then we check each column and include those the user has SELECT
	 * rights on.  Additionally, we always include columns the user provided
	 * data for.
	 */
	aclresult = pg_class_aclcheck(reloid, GetUserId(), ACL_SELECT);
	if (aclresult != ACLCHECK_OK)
	{
		/* Set up the buffer for the column list */
		initStringInfo(&collist);
		appendStringInfoChar(&collist, '(');
	}
	else
		table_perm = any_perm = true;

	/* Make sure the tuple is fully deconstructed */
	slot_getallattrs(slot);

	for (i = 0; i < tupdesc->natts; i++)
	{
		bool		column_perm = false;
		char	   *val;
		int			vallen;
		Form_pg_attribute att = TupleDescAttr(tupdesc, i);

		/* ignore dropped columns */
		if (att->attisdropped)
			continue;

		if (!table_perm)
		{
			/*
			 * No table-level SELECT, so need to make sure they either have
			 * SELECT rights on the column or that they have provided the data
			 * for the column.  If not, omit this column from the error
			 * message.
			 */
			aclresult = pg_attribute_aclcheck(reloid, att->attnum,
											  GetUserId(), ACL_SELECT);
			if (bms_is_member(att->attnum - FirstLowInvalidHeapAttributeNumber,
							  modifiedCols) || aclresult == ACLCHECK_OK)
			{
				column_perm = any_perm = true;

				if (write_comma_collist)
					appendStringInfoString(&collist, ", ");
				else
					write_comma_collist = true;

				appendStringInfoString(&collist, NameStr(att->attname));
			}
		}

		if (table_perm || column_perm)
		{
			if (slot->tts_isnull[i])
				val = "null";
			else
			{
				Oid			foutoid;
				bool		typisvarlena;

				getTypeOutputInfo(att->atttypid,
								  &foutoid, &typisvarlena);
				val = OidOutputFunctionCall(foutoid, slot->tts_values[i]);
			}

			if (write_comma)
				appendStringInfoString(&buf, ", ");
			else
				write_comma = true;

			/* truncate if needed */
			vallen = strlen(val);
			if (vallen <= maxfieldlen)
				appendBinaryStringInfo(&buf, val, vallen);
			else
			{
				vallen = pg_mbcliplen(val, vallen, maxfieldlen);
				appendBinaryStringInfo(&buf, val, vallen);
				appendStringInfoString(&buf, "...");
			}
		}
	}

	/* If we end up with zero columns being returned, then return NULL. */
	if (!any_perm)
		return NULL;

	appendStringInfoChar(&buf, ')');

	if (!table_perm)
	{
		appendStringInfoString(&collist, ") = ");
		appendBinaryStringInfo(&collist, buf.data, buf.len);

		return collist.data;
	}

	return buf.data;
}
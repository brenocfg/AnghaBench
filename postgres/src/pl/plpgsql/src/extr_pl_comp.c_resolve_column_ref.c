#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  location; int /*<<< orphan*/  fields; } ;
struct TYPE_17__ {scalar_t__* datums; } ;
struct TYPE_16__ {int /*<<< orphan*/  ns; TYPE_1__* func; } ;
struct TYPE_15__ {int itemtype; int itemno; } ;
struct TYPE_14__ {int firstfield; } ;
struct TYPE_13__ {size_t recparentno; int nextfield; int /*<<< orphan*/  fieldname; int /*<<< orphan*/  dtype; } ;
struct TYPE_12__ {TYPE_6__* cur_estate; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  TYPE_2__ PLpgSQL_recfield ;
typedef  TYPE_3__ PLpgSQL_rec ;
typedef  TYPE_4__ PLpgSQL_nsitem ;
typedef  TYPE_5__ PLpgSQL_expr ;
typedef  TYPE_6__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_7__ ColumnRef ;

/* Variables and functions */
 int /*<<< orphan*/  A_Star ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 int IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLPGSQL_DTYPE_RECFIELD ; 
#define  PLPGSQL_NSTYPE_REC 129 
#define  PLPGSQL_NSTYPE_VAR 128 
 int /*<<< orphan*/  String ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char const*) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 scalar_t__ lsecond (int /*<<< orphan*/ ) ; 
 scalar_t__ lthird (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_datum_param (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* plpgsql_ns_lookup (int /*<<< orphan*/ ,int,char const*,char const*,char const*,int*) ; 
 char* strVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static Node *
resolve_column_ref(ParseState *pstate, PLpgSQL_expr *expr,
				   ColumnRef *cref, bool error_if_no_field)
{
	PLpgSQL_execstate *estate;
	PLpgSQL_nsitem *nse;
	const char *name1;
	const char *name2 = NULL;
	const char *name3 = NULL;
	const char *colname = NULL;
	int			nnames;
	int			nnames_scalar = 0;
	int			nnames_wholerow = 0;
	int			nnames_field = 0;

	/*
	 * We use the function's current estate to resolve parameter data types.
	 * This is really pretty bogus because there is no provision for updating
	 * plans when those types change ...
	 */
	estate = expr->func->cur_estate;

	/*----------
	 * The allowed syntaxes are:
	 *
	 * A		Scalar variable reference, or whole-row record reference.
	 * A.B		Qualified scalar or whole-row reference, or field reference.
	 * A.B.C	Qualified record field reference.
	 * A.*		Whole-row record reference.
	 * A.B.*	Qualified whole-row record reference.
	 *----------
	 */
	switch (list_length(cref->fields))
	{
		case 1:
			{
				Node	   *field1 = (Node *) linitial(cref->fields);

				Assert(IsA(field1, String));
				name1 = strVal(field1);
				nnames_scalar = 1;
				nnames_wholerow = 1;
				break;
			}
		case 2:
			{
				Node	   *field1 = (Node *) linitial(cref->fields);
				Node	   *field2 = (Node *) lsecond(cref->fields);

				Assert(IsA(field1, String));
				name1 = strVal(field1);

				/* Whole-row reference? */
				if (IsA(field2, A_Star))
				{
					/* Set name2 to prevent matches to scalar variables */
					name2 = "*";
					nnames_wholerow = 1;
					break;
				}

				Assert(IsA(field2, String));
				name2 = strVal(field2);
				colname = name2;
				nnames_scalar = 2;
				nnames_wholerow = 2;
				nnames_field = 1;
				break;
			}
		case 3:
			{
				Node	   *field1 = (Node *) linitial(cref->fields);
				Node	   *field2 = (Node *) lsecond(cref->fields);
				Node	   *field3 = (Node *) lthird(cref->fields);

				Assert(IsA(field1, String));
				name1 = strVal(field1);
				Assert(IsA(field2, String));
				name2 = strVal(field2);

				/* Whole-row reference? */
				if (IsA(field3, A_Star))
				{
					/* Set name3 to prevent matches to scalar variables */
					name3 = "*";
					nnames_wholerow = 2;
					break;
				}

				Assert(IsA(field3, String));
				name3 = strVal(field3);
				colname = name3;
				nnames_field = 2;
				break;
			}
		default:
			/* too many names, ignore */
			return NULL;
	}

	nse = plpgsql_ns_lookup(expr->ns, false,
							name1, name2, name3,
							&nnames);

	if (nse == NULL)
		return NULL;			/* name not known to plpgsql */

	switch (nse->itemtype)
	{
		case PLPGSQL_NSTYPE_VAR:
			if (nnames == nnames_scalar)
				return make_datum_param(expr, nse->itemno, cref->location);
			break;
		case PLPGSQL_NSTYPE_REC:
			if (nnames == nnames_wholerow)
				return make_datum_param(expr, nse->itemno, cref->location);
			if (nnames == nnames_field)
			{
				/* colname could be a field in this record */
				PLpgSQL_rec *rec = (PLpgSQL_rec *) estate->datums[nse->itemno];
				int			i;

				/* search for a datum referencing this field */
				i = rec->firstfield;
				while (i >= 0)
				{
					PLpgSQL_recfield *fld = (PLpgSQL_recfield *) estate->datums[i];

					Assert(fld->dtype == PLPGSQL_DTYPE_RECFIELD &&
						   fld->recparentno == nse->itemno);
					if (strcmp(fld->fieldname, colname) == 0)
					{
						return make_datum_param(expr, i, cref->location);
					}
					i = fld->nextfield;
				}

				/*
				 * We should not get here, because a RECFIELD datum should
				 * have been built at parse time for every possible qualified
				 * reference to fields of this record.  But if we do, handle
				 * it like field-not-found: throw error or return NULL.
				 */
				if (error_if_no_field)
					ereport(ERROR,
							(errcode(ERRCODE_UNDEFINED_COLUMN),
							 errmsg("record \"%s\" has no field \"%s\"",
									(nnames_field == 1) ? name1 : name2,
									colname),
							 parser_errposition(pstate, cref->location)));
			}
			break;
		default:
			elog(ERROR, "unrecognized plpgsql itemtype: %d", nse->itemtype);
	}

	/* Name format doesn't match the plpgsql variable type */
	return NULL;
}
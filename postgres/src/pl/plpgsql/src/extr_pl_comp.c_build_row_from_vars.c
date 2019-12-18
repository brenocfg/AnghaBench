#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_13__ {int /*<<< orphan*/  rectypeid; } ;
struct TYPE_12__ {char* refname; int lineno; int nfields; int /*<<< orphan*/  rowtupdesc; int /*<<< orphan*/ * varnos; int /*<<< orphan*/ * fieldnames; int /*<<< orphan*/  dtype; } ;
struct TYPE_11__ {TYPE_1__* datatype; } ;
struct TYPE_10__ {int dtype; int /*<<< orphan*/  refname; int /*<<< orphan*/  dno; int /*<<< orphan*/  isconst; } ;
struct TYPE_9__ {int atttypmod; int /*<<< orphan*/  collation; int /*<<< orphan*/  typoid; } ;
typedef  TYPE_2__ PLpgSQL_variable ;
typedef  TYPE_3__ PLpgSQL_var ;
typedef  TYPE_4__ PLpgSQL_row ;
typedef  TYPE_5__ PLpgSQL_rec ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
#define  PLPGSQL_DTYPE_PROMISE 130 
#define  PLPGSQL_DTYPE_REC 129 
 int /*<<< orphan*/  PLPGSQL_DTYPE_ROW ; 
#define  PLPGSQL_DTYPE_VAR 128 
 int /*<<< orphan*/  TupleDescInitEntry (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupleDescInitEntryCollation (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 void* palloc (int) ; 
 TYPE_4__* palloc0 (int) ; 

__attribute__((used)) static PLpgSQL_row *
build_row_from_vars(PLpgSQL_variable **vars, int numvars)
{
	PLpgSQL_row *row;
	int			i;

	row = palloc0(sizeof(PLpgSQL_row));
	row->dtype = PLPGSQL_DTYPE_ROW;
	row->refname = "(unnamed row)";
	row->lineno = -1;
	row->rowtupdesc = CreateTemplateTupleDesc(numvars);
	row->nfields = numvars;
	row->fieldnames = palloc(numvars * sizeof(char *));
	row->varnos = palloc(numvars * sizeof(int));

	for (i = 0; i < numvars; i++)
	{
		PLpgSQL_variable *var = vars[i];
		Oid			typoid;
		int32		typmod;
		Oid			typcoll;

		/* Member vars of a row should never be const */
		Assert(!var->isconst);

		switch (var->dtype)
		{
			case PLPGSQL_DTYPE_VAR:
			case PLPGSQL_DTYPE_PROMISE:
				typoid = ((PLpgSQL_var *) var)->datatype->typoid;
				typmod = ((PLpgSQL_var *) var)->datatype->atttypmod;
				typcoll = ((PLpgSQL_var *) var)->datatype->collation;
				break;

			case PLPGSQL_DTYPE_REC:
				/* shouldn't need to revalidate rectypeid already... */
				typoid = ((PLpgSQL_rec *) var)->rectypeid;
				typmod = -1;	/* don't know typmod, if it's used at all */
				typcoll = InvalidOid;	/* composite types have no collation */
				break;

			default:
				elog(ERROR, "unrecognized dtype: %d", var->dtype);
				typoid = InvalidOid;	/* keep compiler quiet */
				typmod = 0;
				typcoll = InvalidOid;
				break;
		}

		row->fieldnames[i] = var->refname;
		row->varnos[i] = var->dno;

		TupleDescInitEntry(row->rowtupdesc, i + 1,
						   var->refname,
						   typoid, typmod,
						   0);
		TupleDescInitEntryCollation(row->rowtupdesc, i + 1, typcoll);
	}

	return row;
}
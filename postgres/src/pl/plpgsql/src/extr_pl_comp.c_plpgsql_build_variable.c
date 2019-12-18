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
struct TYPE_7__ {int ttype; int /*<<< orphan*/  typoid; } ;
struct TYPE_6__ {int lineno; int isnull; int freeval; int /*<<< orphan*/  dno; int /*<<< orphan*/  value; TYPE_2__* datatype; int /*<<< orphan*/  refname; int /*<<< orphan*/  dtype; } ;
typedef  int /*<<< orphan*/  PLpgSQL_variable ;
typedef  TYPE_1__ PLpgSQL_var ;
typedef  TYPE_2__ PLpgSQL_type ;
typedef  int /*<<< orphan*/  PLpgSQL_rec ;
typedef  int /*<<< orphan*/  PLpgSQL_datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PLPGSQL_DTYPE_VAR ; 
 int /*<<< orphan*/  PLPGSQL_NSTYPE_VAR ; 
#define  PLPGSQL_TTYPE_PSEUDO 130 
#define  PLPGSQL_TTYPE_REC 129 
#define  PLPGSQL_TTYPE_SCALAR 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc0 (int) ; 
 int /*<<< orphan*/  plpgsql_adddatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * plpgsql_build_record (char const*,int,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plpgsql_ns_additem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pstrdup (char const*) ; 

PLpgSQL_variable *
plpgsql_build_variable(const char *refname, int lineno, PLpgSQL_type *dtype,
					   bool add2namespace)
{
	PLpgSQL_variable *result;

	switch (dtype->ttype)
	{
		case PLPGSQL_TTYPE_SCALAR:
			{
				/* Ordinary scalar datatype */
				PLpgSQL_var *var;

				var = palloc0(sizeof(PLpgSQL_var));
				var->dtype = PLPGSQL_DTYPE_VAR;
				var->refname = pstrdup(refname);
				var->lineno = lineno;
				var->datatype = dtype;
				/* other fields are left as 0, might be changed by caller */

				/* preset to NULL */
				var->value = 0;
				var->isnull = true;
				var->freeval = false;

				plpgsql_adddatum((PLpgSQL_datum *) var);
				if (add2namespace)
					plpgsql_ns_additem(PLPGSQL_NSTYPE_VAR,
									   var->dno,
									   refname);
				result = (PLpgSQL_variable *) var;
				break;
			}
		case PLPGSQL_TTYPE_REC:
			{
				/* Composite type -- build a record variable */
				PLpgSQL_rec *rec;

				rec = plpgsql_build_record(refname, lineno,
										   dtype, dtype->typoid,
										   add2namespace);
				result = (PLpgSQL_variable *) rec;
				break;
			}
		case PLPGSQL_TTYPE_PSEUDO:
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("variable \"%s\" has pseudo-type %s",
							refname, format_type_be(dtype->typoid))));
			result = NULL;		/* keep compiler quiet */
			break;
		default:
			elog(ERROR, "unrecognized ttype: %d", dtype->ttype);
			result = NULL;		/* keep compiler quiet */
			break;
	}

	return result;
}
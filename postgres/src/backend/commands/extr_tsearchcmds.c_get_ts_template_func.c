#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  DefElem ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
#define  Anum_pg_ts_template_tmplinit 129 
#define  Anum_pg_ts_template_tmpllexize 128 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ INTERNALOID ; 
 scalar_t__ LookupFuncName (int /*<<< orphan*/ *,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/ * defGetQualifiedName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 int /*<<< orphan*/  func_signature_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ get_func_rettype (scalar_t__) ; 

__attribute__((used)) static Datum
get_ts_template_func(DefElem *defel, int attnum)
{
	List	   *funcName = defGetQualifiedName(defel);
	Oid			typeId[4];
	Oid			retTypeId;
	int			nargs;
	Oid			procOid;

	retTypeId = INTERNALOID;
	typeId[0] = INTERNALOID;
	typeId[1] = INTERNALOID;
	typeId[2] = INTERNALOID;
	typeId[3] = INTERNALOID;
	switch (attnum)
	{
		case Anum_pg_ts_template_tmplinit:
			nargs = 1;
			break;
		case Anum_pg_ts_template_tmpllexize:
			nargs = 4;
			break;
		default:
			/* should not be here */
			elog(ERROR, "unrecognized attribute for text search template: %d",
				 attnum);
			nargs = 0;			/* keep compiler quiet */
	}

	procOid = LookupFuncName(funcName, nargs, typeId, false);
	if (get_func_rettype(procOid) != retTypeId)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("function %s should return type %s",
						func_signature_string(funcName, nargs, NIL, typeId),
						format_type_be(retTypeId))));

	return ObjectIdGetDatum(procOid);
}
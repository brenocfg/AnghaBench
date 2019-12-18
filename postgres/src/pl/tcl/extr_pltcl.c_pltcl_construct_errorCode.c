#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
struct TYPE_3__ {scalar_t__ internalpos; scalar_t__ lineno; scalar_t__ funcname; scalar_t__ filename; scalar_t__ internalquery; scalar_t__ constraint_name; scalar_t__ datatype_name; scalar_t__ column_name; scalar_t__ table_name; scalar_t__ schema_name; scalar_t__ context; scalar_t__ hint; scalar_t__ detail; scalar_t__ message; int /*<<< orphan*/  sqlerrcode; } ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 char* PG_VERSION ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_NewIntObj (scalar_t__) ; 
 int /*<<< orphan*/ * Tcl_NewObj () ; 
 int /*<<< orphan*/  Tcl_NewStringObj (char*,int) ; 
 int /*<<< orphan*/  Tcl_SetObjErrorCode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UTF_BEGIN ; 
 char* UTF_E2U (scalar_t__) ; 
 int /*<<< orphan*/  UTF_END ; 
 char* pltcl_get_condition_name (int /*<<< orphan*/ ) ; 
 char* unpack_sql_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pltcl_construct_errorCode(Tcl_Interp *interp, ErrorData *edata)
{
	Tcl_Obj    *obj = Tcl_NewObj();

	Tcl_ListObjAppendElement(interp, obj,
							 Tcl_NewStringObj("POSTGRES", -1));
	Tcl_ListObjAppendElement(interp, obj,
							 Tcl_NewStringObj(PG_VERSION, -1));
	Tcl_ListObjAppendElement(interp, obj,
							 Tcl_NewStringObj("SQLSTATE", -1));
	Tcl_ListObjAppendElement(interp, obj,
							 Tcl_NewStringObj(unpack_sql_state(edata->sqlerrcode), -1));
	Tcl_ListObjAppendElement(interp, obj,
							 Tcl_NewStringObj("condition", -1));
	Tcl_ListObjAppendElement(interp, obj,
							 Tcl_NewStringObj(pltcl_get_condition_name(edata->sqlerrcode), -1));
	Tcl_ListObjAppendElement(interp, obj,
							 Tcl_NewStringObj("message", -1));
	UTF_BEGIN;
	Tcl_ListObjAppendElement(interp, obj,
							 Tcl_NewStringObj(UTF_E2U(edata->message), -1));
	UTF_END;
	if (edata->detail)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("detail", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->detail), -1));
		UTF_END;
	}
	if (edata->hint)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("hint", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->hint), -1));
		UTF_END;
	}
	if (edata->context)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("context", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->context), -1));
		UTF_END;
	}
	if (edata->schema_name)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("schema", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->schema_name), -1));
		UTF_END;
	}
	if (edata->table_name)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("table", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->table_name), -1));
		UTF_END;
	}
	if (edata->column_name)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("column", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->column_name), -1));
		UTF_END;
	}
	if (edata->datatype_name)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("datatype", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->datatype_name), -1));
		UTF_END;
	}
	if (edata->constraint_name)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("constraint", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->constraint_name), -1));
		UTF_END;
	}
	/* cursorpos is never interesting here; report internal query/pos */
	if (edata->internalquery)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("statement", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->internalquery), -1));
		UTF_END;
	}
	if (edata->internalpos > 0)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("cursor_position", -1));
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewIntObj(edata->internalpos));
	}
	if (edata->filename)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("filename", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->filename), -1));
		UTF_END;
	}
	if (edata->lineno > 0)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("lineno", -1));
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewIntObj(edata->lineno));
	}
	if (edata->funcname)
	{
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj("funcname", -1));
		UTF_BEGIN;
		Tcl_ListObjAppendElement(interp, obj,
								 Tcl_NewStringObj(UTF_E2U(edata->funcname), -1));
		UTF_END;
	}

	Tcl_SetObjErrorCode(interp, obj);
}
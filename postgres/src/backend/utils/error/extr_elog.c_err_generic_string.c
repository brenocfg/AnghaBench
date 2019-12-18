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
struct TYPE_3__ {int /*<<< orphan*/  constraint_name; int /*<<< orphan*/  assoc_context; int /*<<< orphan*/  datatype_name; int /*<<< orphan*/  column_name; int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; } ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STACK_DEPTH () ; 
 int /*<<< orphan*/  ERROR ; 
#define  PG_DIAG_COLUMN_NAME 132 
#define  PG_DIAG_CONSTRAINT_NAME 131 
#define  PG_DIAG_DATATYPE_NAME 130 
#define  PG_DIAG_SCHEMA_NAME 129 
#define  PG_DIAG_TABLE_NAME 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* errordata ; 
 size_t errordata_stack_depth ; 
 int /*<<< orphan*/  set_errdata_field (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 

int
err_generic_string(int field, const char *str)
{
	ErrorData  *edata = &errordata[errordata_stack_depth];

	/* we don't bother incrementing recursion_depth */
	CHECK_STACK_DEPTH();

	switch (field)
	{
		case PG_DIAG_SCHEMA_NAME:
			set_errdata_field(edata->assoc_context, &edata->schema_name, str);
			break;
		case PG_DIAG_TABLE_NAME:
			set_errdata_field(edata->assoc_context, &edata->table_name, str);
			break;
		case PG_DIAG_COLUMN_NAME:
			set_errdata_field(edata->assoc_context, &edata->column_name, str);
			break;
		case PG_DIAG_DATATYPE_NAME:
			set_errdata_field(edata->assoc_context, &edata->datatype_name, str);
			break;
		case PG_DIAG_CONSTRAINT_NAME:
			set_errdata_field(edata->assoc_context, &edata->constraint_name, str);
			break;
		default:
			elog(ERROR, "unsupported ErrorData field id: %d", field);
			break;
	}

	return 0;					/* return value does not matter */
}
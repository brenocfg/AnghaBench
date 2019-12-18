#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  subscript; } ;
struct TYPE_10__ {int dtype; } ;
struct TYPE_9__ {scalar_t__ use_count; int ndatums; int /*<<< orphan*/ * fn_cxt; int /*<<< orphan*/ * action; TYPE_4__** datums; } ;
struct TYPE_8__ {int /*<<< orphan*/  default_val; } ;
struct TYPE_7__ {int /*<<< orphan*/  cursor_explicit_expr; int /*<<< orphan*/  default_val; } ;
typedef  TYPE_1__ PLpgSQL_var ;
typedef  TYPE_2__ PLpgSQL_rec ;
typedef  TYPE_3__ PLpgSQL_function ;
typedef  TYPE_4__ PLpgSQL_datum ;
typedef  TYPE_5__ PLpgSQL_arrayelem ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
#define  PLPGSQL_DTYPE_ARRAYELEM 133 
#define  PLPGSQL_DTYPE_PROMISE 132 
#define  PLPGSQL_DTYPE_REC 131 
#define  PLPGSQL_DTYPE_RECFIELD 130 
#define  PLPGSQL_DTYPE_ROW 129 
#define  PLPGSQL_DTYPE_VAR 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_expr (int /*<<< orphan*/ ) ; 

void
plpgsql_free_function_memory(PLpgSQL_function *func)
{
	int			i;

	/* Better not call this on an in-use function */
	Assert(func->use_count == 0);

	/* Release plans associated with variable declarations */
	for (i = 0; i < func->ndatums; i++)
	{
		PLpgSQL_datum *d = func->datums[i];

		switch (d->dtype)
		{
			case PLPGSQL_DTYPE_VAR:
			case PLPGSQL_DTYPE_PROMISE:
				{
					PLpgSQL_var *var = (PLpgSQL_var *) d;

					free_expr(var->default_val);
					free_expr(var->cursor_explicit_expr);
				}
				break;
			case PLPGSQL_DTYPE_ROW:
				break;
			case PLPGSQL_DTYPE_REC:
				{
					PLpgSQL_rec *rec = (PLpgSQL_rec *) d;

					free_expr(rec->default_val);
				}
				break;
			case PLPGSQL_DTYPE_RECFIELD:
				break;
			case PLPGSQL_DTYPE_ARRAYELEM:
				free_expr(((PLpgSQL_arrayelem *) d)->subscript);
				break;
			default:
				elog(ERROR, "unrecognized data type: %d", d->dtype);
		}
	}
	func->ndatums = 0;

	/* Release plans in statement tree */
	if (func->action)
		free_block(func->action);
	func->action = NULL;

	/*
	 * And finally, release all memory except the PLpgSQL_function struct
	 * itself (which has to be kept around because there may be multiple
	 * fn_extra pointers to it).
	 */
	if (func->fn_cxt)
		MemoryContextDelete(func->fn_cxt);
	func->fn_cxt = NULL;
}
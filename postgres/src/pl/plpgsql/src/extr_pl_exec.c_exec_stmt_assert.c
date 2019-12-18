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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int /*<<< orphan*/ * message; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ PLpgSQL_stmt_assert ;
typedef  int /*<<< orphan*/  PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_ASSERT_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 int PLPGSQL_RC_OK ; 
 char* convert_value_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  errmsg_internal (char*,char*) ; 
 int exec_eval_boolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  exec_eval_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_eval_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plpgsql_check_asserts ; 

__attribute__((used)) static int
exec_stmt_assert(PLpgSQL_execstate *estate, PLpgSQL_stmt_assert *stmt)
{
	bool		value;
	bool		isnull;

	/* do nothing when asserts are not enabled */
	if (!plpgsql_check_asserts)
		return PLPGSQL_RC_OK;

	value = exec_eval_boolean(estate, stmt->cond, &isnull);
	exec_eval_cleanup(estate);

	if (isnull || !value)
	{
		char	   *message = NULL;

		if (stmt->message != NULL)
		{
			Datum		val;
			Oid			typeid;
			int32		typmod;

			val = exec_eval_expr(estate, stmt->message,
								 &isnull, &typeid, &typmod);
			if (!isnull)
				message = convert_value_to_string(estate, val, typeid);
			/* we mustn't do exec_eval_cleanup here */
		}

		ereport(ERROR,
				(errcode(ERRCODE_ASSERT_FAILURE),
				 message ? errmsg_internal("%s", message) :
				 errmsg("assertion failed")));
	}

	return PLPGSQL_RC_OK;
}
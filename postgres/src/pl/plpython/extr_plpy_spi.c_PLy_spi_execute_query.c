#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* curr_proc; } ;
struct TYPE_4__ {int /*<<< orphan*/  fn_readonly; } ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PLyExecutionContext ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 TYPE_2__* PLy_current_execution_context () ; 
 int /*<<< orphan*/  PLy_exc_spi_error ; 
 int /*<<< orphan*/  PLy_exception_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PLy_spi_execute_fetch_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLy_spi_subtransaction_abort (int /*<<< orphan*/  volatile,int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  PLy_spi_subtransaction_begin (int /*<<< orphan*/  volatile,int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  PLy_spi_subtransaction_commit (int /*<<< orphan*/  volatile,int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int SPI_execute (char*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  SPI_processed ; 
 int /*<<< orphan*/  SPI_result_code_string (int) ; 
 int /*<<< orphan*/  SPI_tuptable ; 
 int /*<<< orphan*/  pg_verifymbstr (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static PyObject *
PLy_spi_execute_query(char *query, long limit)
{
	int			rv;
	volatile MemoryContext oldcontext;
	volatile ResourceOwner oldowner;
	PyObject   *ret = NULL;

	oldcontext = CurrentMemoryContext;
	oldowner = CurrentResourceOwner;

	PLy_spi_subtransaction_begin(oldcontext, oldowner);

	PG_TRY();
	{
		PLyExecutionContext *exec_ctx = PLy_current_execution_context();

		pg_verifymbstr(query, strlen(query), false);
		rv = SPI_execute(query, exec_ctx->curr_proc->fn_readonly, limit);
		ret = PLy_spi_execute_fetch_result(SPI_tuptable, SPI_processed, rv);

		PLy_spi_subtransaction_commit(oldcontext, oldowner);
	}
	PG_CATCH();
	{
		PLy_spi_subtransaction_abort(oldcontext, oldowner);
		return NULL;
	}
	PG_END_TRY();

	if (rv < 0)
	{
		Py_XDECREF(ret);
		PLy_exception_set(PLy_exc_spi_error,
						  "SPI_execute failed: %s",
						  SPI_result_code_string(rv));
		return NULL;
	}

	return ret;
}
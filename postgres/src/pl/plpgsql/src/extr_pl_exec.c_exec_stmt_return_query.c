#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  TupleConversionMap ;
struct TYPE_21__ {scalar_t__ eval_processed; int /*<<< orphan*/ * tuple_store; int /*<<< orphan*/  tuple_store_desc; int /*<<< orphan*/  retisset; } ;
struct TYPE_20__ {int /*<<< orphan*/  params; int /*<<< orphan*/ * dynquery; int /*<<< orphan*/ * query; } ;
struct TYPE_19__ {int /*<<< orphan*/  tupDesc; } ;
struct TYPE_18__ {int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__* Portal ;
typedef  TYPE_2__ PLpgSQL_stmt_return_query ;
typedef  TYPE_3__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int PLPGSQL_RC_OK ; 
 int /*<<< orphan*/  SPI_cursor_close (TYPE_1__*) ; 
 int /*<<< orphan*/  SPI_cursor_fetch (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  SPI_freetuptable (TYPE_14__*) ; 
 scalar_t__ SPI_processed ; 
 TYPE_14__* SPI_tuptable ; 
 int /*<<< orphan*/ * convert_tuples_by_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_1__* exec_dynquery_with_params (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_eval_cleanup (TYPE_3__*) ; 
 int /*<<< orphan*/  exec_init_tuple_store (TYPE_3__*) ; 
 int /*<<< orphan*/  exec_run_select (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  exec_set_found (TYPE_3__*,int) ; 
 int /*<<< orphan*/  execute_attr_map_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_eval_mcontext (TYPE_3__*) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_puttuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_stmt_return_query(PLpgSQL_execstate *estate,
					   PLpgSQL_stmt_return_query *stmt)
{
	Portal		portal;
	uint64		processed = 0;
	TupleConversionMap *tupmap;
	MemoryContext oldcontext;

	if (!estate->retisset)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("cannot use RETURN QUERY in a non-SETOF function")));

	if (estate->tuple_store == NULL)
		exec_init_tuple_store(estate);

	if (stmt->query != NULL)
	{
		/* static query */
		exec_run_select(estate, stmt->query, 0, &portal);
	}
	else
	{
		/* RETURN QUERY EXECUTE */
		Assert(stmt->dynquery != NULL);
		portal = exec_dynquery_with_params(estate, stmt->dynquery,
										   stmt->params, NULL,
										   0);
	}

	/* Use eval_mcontext for tuple conversion work */
	oldcontext = MemoryContextSwitchTo(get_eval_mcontext(estate));

	tupmap = convert_tuples_by_position(portal->tupDesc,
										estate->tuple_store_desc,
										gettext_noop("structure of query does not match function result type"));

	while (true)
	{
		uint64		i;

		SPI_cursor_fetch(portal, true, 50);

		/* SPI will have changed CurrentMemoryContext */
		MemoryContextSwitchTo(get_eval_mcontext(estate));

		if (SPI_processed == 0)
			break;

		for (i = 0; i < SPI_processed; i++)
		{
			HeapTuple	tuple = SPI_tuptable->vals[i];

			if (tupmap)
				tuple = execute_attr_map_tuple(tuple, tupmap);
			tuplestore_puttuple(estate->tuple_store, tuple);
			if (tupmap)
				heap_freetuple(tuple);
			processed++;
		}

		SPI_freetuptable(SPI_tuptable);
	}

	SPI_freetuptable(SPI_tuptable);
	SPI_cursor_close(portal);

	MemoryContextSwitchTo(oldcontext);
	exec_eval_cleanup(estate);

	estate->eval_processed = processed;
	exec_set_found(estate, processed != 0);

	return PLPGSQL_RC_OK;
}
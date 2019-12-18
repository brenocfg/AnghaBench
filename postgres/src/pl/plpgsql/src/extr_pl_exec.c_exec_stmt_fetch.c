#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_19__ {scalar_t__ eval_processed; scalar_t__* datums; } ;
struct TYPE_18__ {long how_many; size_t curvar; int /*<<< orphan*/  direction; TYPE_1__* target; int /*<<< orphan*/  is_move; scalar_t__ expr; } ;
struct TYPE_17__ {int /*<<< orphan*/  value; int /*<<< orphan*/  refname; scalar_t__ isnull; } ;
struct TYPE_16__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ ** vals; } ;
struct TYPE_15__ {size_t dno; } ;
typedef  TYPE_2__ SPITupleTable ;
typedef  int /*<<< orphan*/ * Portal ;
typedef  int /*<<< orphan*/  PLpgSQL_variable ;
typedef  TYPE_3__ PLpgSQL_var ;
typedef  TYPE_4__ PLpgSQL_stmt_fetch ;
typedef  TYPE_5__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_CURSOR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int PLPGSQL_RC_OK ; 
 int /*<<< orphan*/ * SPI_cursor_find (char*) ; 
 int /*<<< orphan*/  SPI_freetuptable (TYPE_2__*) ; 
 scalar_t__ SPI_processed ; 
 int /*<<< orphan*/  SPI_scroll_cursor_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  SPI_scroll_cursor_move (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 TYPE_2__* SPI_tuptable ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  exec_eval_cleanup (TYPE_5__*) ; 
 long exec_eval_integer (TYPE_5__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  exec_move_row (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_set_found (TYPE_5__*,int) ; 
 int /*<<< orphan*/  get_eval_mcontext (TYPE_5__*) ; 

__attribute__((used)) static int
exec_stmt_fetch(PLpgSQL_execstate *estate, PLpgSQL_stmt_fetch *stmt)
{
	PLpgSQL_var *curvar;
	long		how_many = stmt->how_many;
	SPITupleTable *tuptab;
	Portal		portal;
	char	   *curname;
	uint64		n;
	MemoryContext oldcontext;

	/* ----------
	 * Get the portal of the cursor by name
	 * ----------
	 */
	curvar = (PLpgSQL_var *) (estate->datums[stmt->curvar]);
	if (curvar->isnull)
		ereport(ERROR,
				(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
				 errmsg("cursor variable \"%s\" is null", curvar->refname)));

	/* Use eval_mcontext for short-lived string */
	oldcontext = MemoryContextSwitchTo(get_eval_mcontext(estate));
	curname = TextDatumGetCString(curvar->value);
	MemoryContextSwitchTo(oldcontext);

	portal = SPI_cursor_find(curname);
	if (portal == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_CURSOR),
				 errmsg("cursor \"%s\" does not exist", curname)));

	/* Calculate position for FETCH_RELATIVE or FETCH_ABSOLUTE */
	if (stmt->expr)
	{
		bool		isnull;

		/* XXX should be doing this in LONG not INT width */
		how_many = exec_eval_integer(estate, stmt->expr, &isnull);

		if (isnull)
			ereport(ERROR,
					(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
					 errmsg("relative or absolute cursor position is null")));

		exec_eval_cleanup(estate);
	}

	if (!stmt->is_move)
	{
		PLpgSQL_variable *target;

		/* ----------
		 * Fetch 1 tuple from the cursor
		 * ----------
		 */
		SPI_scroll_cursor_fetch(portal, stmt->direction, how_many);
		tuptab = SPI_tuptable;
		n = SPI_processed;

		/* ----------
		 * Set the target appropriately.
		 * ----------
		 */
		target = (PLpgSQL_variable *) estate->datums[stmt->target->dno];
		if (n == 0)
			exec_move_row(estate, target, NULL, tuptab->tupdesc);
		else
			exec_move_row(estate, target, tuptab->vals[0], tuptab->tupdesc);

		exec_eval_cleanup(estate);
		SPI_freetuptable(tuptab);
	}
	else
	{
		/* Move the cursor */
		SPI_scroll_cursor_move(portal, stmt->direction, how_many);
		n = SPI_processed;
	}

	/* Set the ROW_COUNT and the global FOUND variable appropriately. */
	estate->eval_processed = n;
	exec_set_found(estate, n != 0);

	return PLPGSQL_RC_OK;
}
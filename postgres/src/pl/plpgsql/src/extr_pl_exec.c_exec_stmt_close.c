#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__* datums; } ;
struct TYPE_8__ {size_t curvar; } ;
struct TYPE_7__ {char* refname; int /*<<< orphan*/  value; scalar_t__ isnull; } ;
typedef  int /*<<< orphan*/ * Portal ;
typedef  TYPE_1__ PLpgSQL_var ;
typedef  TYPE_2__ PLpgSQL_stmt_close ;
typedef  TYPE_3__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_CURSOR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int PLPGSQL_RC_OK ; 
 int /*<<< orphan*/  SPI_cursor_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SPI_cursor_find (char*) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  get_eval_mcontext (TYPE_3__*) ; 

__attribute__((used)) static int
exec_stmt_close(PLpgSQL_execstate *estate, PLpgSQL_stmt_close *stmt)
{
	PLpgSQL_var *curvar;
	Portal		portal;
	char	   *curname;
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

	/* ----------
	 * And close it.
	 * ----------
	 */
	SPI_cursor_close(portal);

	return PLPGSQL_RC_OK;
}
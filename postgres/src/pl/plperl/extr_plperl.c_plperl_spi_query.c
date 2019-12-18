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
struct TYPE_7__ {int /*<<< orphan*/  message; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/ * SPIPlanPtr ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  TYPE_1__* Portal ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ ErrorData ;

/* Variables and functions */
 int /*<<< orphan*/  BeginInternalSubTransaction (int /*<<< orphan*/ *) ; 
 TYPE_2__* CopyErrorData () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FlushErrorState () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PinPortal (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCurrentSubTransaction () ; 
 int /*<<< orphan*/  RollbackAndReleaseCurrentSubTransaction () ; 
 TYPE_1__* SPI_cursor_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SPI_freeplan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SPI_prepare (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPI_result ; 
 int /*<<< orphan*/  SPI_result_code_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_spi_usage_allowed () ; 
 int /*<<< orphan*/  croak_cstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cstr2sv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_verifymbstr (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

SV *
plperl_spi_query(char *query)
{
	SV		   *cursor;

	/*
	 * Execute the query inside a sub-transaction, so we can cope with errors
	 * sanely
	 */
	MemoryContext oldcontext = CurrentMemoryContext;
	ResourceOwner oldowner = CurrentResourceOwner;

	check_spi_usage_allowed();

	BeginInternalSubTransaction(NULL);
	/* Want to run inside function's memory context */
	MemoryContextSwitchTo(oldcontext);

	PG_TRY();
	{
		SPIPlanPtr	plan;
		Portal		portal;

		/* Make sure the query is validly encoded */
		pg_verifymbstr(query, strlen(query), false);

		/* Create a cursor for the query */
		plan = SPI_prepare(query, 0, NULL);
		if (plan == NULL)
			elog(ERROR, "SPI_prepare() failed:%s",
				 SPI_result_code_string(SPI_result));

		portal = SPI_cursor_open(NULL, plan, NULL, NULL, false);
		SPI_freeplan(plan);
		if (portal == NULL)
			elog(ERROR, "SPI_cursor_open() failed:%s",
				 SPI_result_code_string(SPI_result));
		cursor = cstr2sv(portal->name);

		PinPortal(portal);

		/* Commit the inner transaction, return to outer xact context */
		ReleaseCurrentSubTransaction();
		MemoryContextSwitchTo(oldcontext);
		CurrentResourceOwner = oldowner;
	}
	PG_CATCH();
	{
		ErrorData  *edata;

		/* Save error info */
		MemoryContextSwitchTo(oldcontext);
		edata = CopyErrorData();
		FlushErrorState();

		/* Abort the inner transaction */
		RollbackAndReleaseCurrentSubTransaction();
		MemoryContextSwitchTo(oldcontext);
		CurrentResourceOwner = oldowner;

		/* Punt the error to Perl */
		croak_cstr(edata->message);

		/* Can't get here, but keep compiler quiet */
		return NULL;
	}
	PG_END_TRY();

	return cursor;
}
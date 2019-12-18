#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  Portal ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 int /*<<< orphan*/  BeginInternalSubTransaction (int /*<<< orphan*/ *) ; 
 TYPE_1__* CopyErrorData () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  FlushErrorState () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PL_sv_undef ; 
 int /*<<< orphan*/  ReleaseCurrentSubTransaction () ; 
 int /*<<< orphan*/  RollbackAndReleaseCurrentSubTransaction () ; 
 int /*<<< orphan*/  SPI_cursor_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_cursor_fetch (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SPI_cursor_find (char*) ; 
 int /*<<< orphan*/  SPI_freetuptable (TYPE_2__*) ; 
 scalar_t__ SPI_processed ; 
 TYPE_2__* SPI_tuptable ; 
 int /*<<< orphan*/  UnpinPortal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_spi_usage_allowed () ; 
 int /*<<< orphan*/  croak_cstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/ * plperl_hash_from_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

SV *
plperl_spi_fetchrow(char *cursor)
{
	SV		   *row;

	/*
	 * Execute the FETCH inside a sub-transaction, so we can cope with errors
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
		dTHX;
		Portal		p = SPI_cursor_find(cursor);

		if (!p)
		{
			row = &PL_sv_undef;
		}
		else
		{
			SPI_cursor_fetch(p, true, 1);
			if (SPI_processed == 0)
			{
				UnpinPortal(p);
				SPI_cursor_close(p);
				row = &PL_sv_undef;
			}
			else
			{
				row = plperl_hash_from_tuple(SPI_tuptable->vals[0],
											 SPI_tuptable->tupdesc,
											 true);
			}
			SPI_freetuptable(SPI_tuptable);
		}

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

	return row;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* query_data; } ;
typedef  TYPE_2__ plperl_query_entry ;
struct TYPE_11__ {int nargs; int /*<<< orphan*/  plan; int /*<<< orphan*/ * argtypioparams; int /*<<< orphan*/ * arginfuncs; int /*<<< orphan*/ * argtypes; } ;
typedef  TYPE_3__ plperl_query_desc ;
struct TYPE_14__ {TYPE_1__* prodesc; } ;
struct TYPE_13__ {int /*<<< orphan*/  query_hash; } ;
struct TYPE_12__ {int /*<<< orphan*/  message; } ;
struct TYPE_9__ {int /*<<< orphan*/  fn_readonly; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HV ;
typedef  TYPE_4__ ErrorData ;
typedef  char Datum ;

/* Variables and functions */
 int /*<<< orphan*/  BeginInternalSubTransaction (int /*<<< orphan*/ *) ; 
 TYPE_4__* CopyErrorData () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FlushErrorState () ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  ReleaseCurrentSubTransaction () ; 
 int /*<<< orphan*/  RollbackAndReleaseCurrentSubTransaction () ; 
 int SPI_execute_plan (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_processed ; 
 int /*<<< orphan*/  SPI_tuptable ; 
 scalar_t__ SvIOK (int /*<<< orphan*/ *) ; 
 int SvIV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_spi_usage_allowed () ; 
 int /*<<< orphan*/  croak_cstr (int /*<<< orphan*/ ) ; 
 TYPE_7__* current_call_data ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* hash_search (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** hv_fetch_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 TYPE_5__* plperl_active_interp ; 
 int /*<<< orphan*/ * plperl_spi_execute_fetch_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char plperl_sv_to_datum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

HV *
plperl_spi_exec_prepared(char *query, HV *attr, int argc, SV **argv)
{
	HV		   *ret_hv;
	SV		  **sv;
	int			i,
				limit,
				spi_rv;
	char	   *nulls;
	Datum	   *argvalues;
	plperl_query_desc *qdesc;
	plperl_query_entry *hash_entry;

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
		dTHX;

		/************************************************************
		 * Fetch the saved plan descriptor, see if it's o.k.
		 ************************************************************/
		hash_entry = hash_search(plperl_active_interp->query_hash, query,
								 HASH_FIND, NULL);
		if (hash_entry == NULL)
			elog(ERROR, "spi_exec_prepared: Invalid prepared query passed");

		qdesc = hash_entry->query_data;
		if (qdesc == NULL)
			elog(ERROR, "spi_exec_prepared: plperl query_hash value vanished");

		if (qdesc->nargs != argc)
			elog(ERROR, "spi_exec_prepared: expected %d argument(s), %d passed",
				 qdesc->nargs, argc);

		/************************************************************
		 * Parse eventual attributes
		 ************************************************************/
		limit = 0;
		if (attr != NULL)
		{
			sv = hv_fetch_string(attr, "limit");
			if (sv && *sv && SvIOK(*sv))
				limit = SvIV(*sv);
		}
		/************************************************************
		 * Set up arguments
		 ************************************************************/
		if (argc > 0)
		{
			nulls = (char *) palloc(argc);
			argvalues = (Datum *) palloc(argc * sizeof(Datum));
		}
		else
		{
			nulls = NULL;
			argvalues = NULL;
		}

		for (i = 0; i < argc; i++)
		{
			bool		isnull;

			argvalues[i] = plperl_sv_to_datum(argv[i],
											  qdesc->argtypes[i],
											  -1,
											  NULL,
											  &qdesc->arginfuncs[i],
											  qdesc->argtypioparams[i],
											  &isnull);
			nulls[i] = isnull ? 'n' : ' ';
		}

		/************************************************************
		 * go
		 ************************************************************/
		spi_rv = SPI_execute_plan(qdesc->plan, argvalues, nulls,
								  current_call_data->prodesc->fn_readonly, limit);
		ret_hv = plperl_spi_execute_fetch_result(SPI_tuptable, SPI_processed,
												 spi_rv);
		if (argc > 0)
		{
			pfree(argvalues);
			pfree(nulls);
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

	return ret_hv;
}
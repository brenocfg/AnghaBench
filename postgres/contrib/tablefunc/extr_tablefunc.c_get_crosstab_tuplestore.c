#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_9__ {int attidx; } ;
typedef  TYPE_1__ crosstab_cat_desc ;
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_11__ {int /*<<< orphan*/ * vals; TYPE_2__* tupdesc; } ;
struct TYPE_10__ {int natts; } ;
typedef  TYPE_3__ SPITupleTable ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  AttInMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  BuildTupleFromCStrings (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ SPI_OK_FINISH ; 
 int SPI_OK_SELECT ; 
 int SPI_connect () ; 
 int SPI_execute (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SPI_finish () ; 
 char* SPI_getvalue (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ SPI_processed ; 
 TYPE_3__* SPI_tuptable ; 
 int /*<<< orphan*/ * TupleDescGetAttInMetadata (TYPE_2__*) ; 
 int /*<<< orphan*/  crosstab_HashTableLookup (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int hash_get_num_entries (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/ * tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_donestoring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_puttuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 
 int /*<<< orphan*/  xpfree (char*) ; 
 int /*<<< orphan*/  xpstrdup (char*,char*) ; 
 int /*<<< orphan*/  xstreq (char*,char*) ; 

__attribute__((used)) static Tuplestorestate *
get_crosstab_tuplestore(char *sql,
						HTAB *crosstab_hash,
						TupleDesc tupdesc,
						MemoryContext per_query_ctx,
						bool randomAccess)
{
	Tuplestorestate *tupstore;
	int			num_categories = hash_get_num_entries(crosstab_hash);
	AttInMetadata *attinmeta = TupleDescGetAttInMetadata(tupdesc);
	char	  **values;
	HeapTuple	tuple;
	int			ret;
	uint64		proc;

	/* initialize our tuplestore (while still in query context!) */
	tupstore = tuplestore_begin_heap(randomAccess, false, work_mem);

	/* Connect to SPI manager */
	if ((ret = SPI_connect()) < 0)
		/* internal error */
		elog(ERROR, "get_crosstab_tuplestore: SPI_connect returned %d", ret);

	/* Now retrieve the crosstab source rows */
	ret = SPI_execute(sql, true, 0);
	proc = SPI_processed;

	/* Check for qualifying tuples */
	if ((ret == SPI_OK_SELECT) && (proc > 0))
	{
		SPITupleTable *spi_tuptable = SPI_tuptable;
		TupleDesc	spi_tupdesc = spi_tuptable->tupdesc;
		int			ncols = spi_tupdesc->natts;
		char	   *rowid;
		char	   *lastrowid = NULL;
		bool		firstpass = true;
		uint64		i;
		int			j;
		int			result_ncols;

		if (num_categories == 0)
		{
			/* no qualifying category tuples */
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("provided \"categories\" SQL must " \
							"return 1 column of at least one row")));
		}

		/*
		 * The provided SQL query must always return at least three columns:
		 *
		 * 1. rowname	the label for each row - column 1 in the final result
		 * 2. category	the label for each value-column in the final result 3.
		 * value	 the values used to populate the value-columns
		 *
		 * If there are more than three columns, the last two are taken as
		 * "category" and "values". The first column is taken as "rowname".
		 * Additional columns (2 thru N-2) are assumed the same for the same
		 * "rowname", and are copied into the result tuple from the first time
		 * we encounter a particular rowname.
		 */
		if (ncols < 3)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("invalid source data SQL statement"),
					 errdetail("The provided SQL must return 3 " \
							   " columns; rowid, category, and values.")));

		result_ncols = (ncols - 2) + num_categories;

		/* Recheck to make sure we tuple descriptor still looks reasonable */
		if (tupdesc->natts != result_ncols)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("invalid return type"),
					 errdetail("Query-specified return " \
							   "tuple has %d columns but crosstab " \
							   "returns %d.", tupdesc->natts, result_ncols)));

		/* allocate space and make sure it's clear */
		values = (char **) palloc0(result_ncols * sizeof(char *));

		for (i = 0; i < proc; i++)
		{
			HeapTuple	spi_tuple;
			crosstab_cat_desc *catdesc;
			char	   *catname;

			/* get the next sql result tuple */
			spi_tuple = spi_tuptable->vals[i];

			/* get the rowid from the current sql result tuple */
			rowid = SPI_getvalue(spi_tuple, spi_tupdesc, 1);

			/*
			 * if we're on a new output row, grab the column values up to
			 * column N-2 now
			 */
			if (firstpass || !xstreq(lastrowid, rowid))
			{
				/*
				 * a new row means we need to flush the old one first, unless
				 * we're on the very first row
				 */
				if (!firstpass)
				{
					/* rowid changed, flush the previous output row */
					tuple = BuildTupleFromCStrings(attinmeta, values);

					tuplestore_puttuple(tupstore, tuple);

					for (j = 0; j < result_ncols; j++)
						xpfree(values[j]);
				}

				values[0] = rowid;
				for (j = 1; j < ncols - 2; j++)
					values[j] = SPI_getvalue(spi_tuple, spi_tupdesc, j + 1);

				/* we're no longer on the first pass */
				firstpass = false;
			}

			/* look up the category and fill in the appropriate column */
			catname = SPI_getvalue(spi_tuple, spi_tupdesc, ncols - 1);

			if (catname != NULL)
			{
				crosstab_HashTableLookup(crosstab_hash, catname, catdesc);

				if (catdesc)
					values[catdesc->attidx + ncols - 2] =
						SPI_getvalue(spi_tuple, spi_tupdesc, ncols);
			}

			xpfree(lastrowid);
			xpstrdup(lastrowid, rowid);
		}

		/* flush the last output row */
		tuple = BuildTupleFromCStrings(attinmeta, values);

		tuplestore_puttuple(tupstore, tuple);
	}

	if (SPI_finish() != SPI_OK_FINISH)
		/* internal error */
		elog(ERROR, "get_crosstab_tuplestore: SPI_finish() failed");

	tuplestore_donestoring(tupstore);

	return tupstore;
}
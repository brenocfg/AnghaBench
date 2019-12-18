#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_10__ {char* catname; scalar_t__ attidx; } ;
typedef  TYPE_1__ crosstab_cat_desc ;
typedef  int /*<<< orphan*/  crosstab_HashEnt ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_13__ {int entrysize; int /*<<< orphan*/  hcxt; int /*<<< orphan*/  keysize; } ;
struct TYPE_12__ {int /*<<< orphan*/ * vals; TYPE_2__* tupdesc; } ;
struct TYPE_11__ {int natts; } ;
typedef  TYPE_3__ SPITupleTable ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_4__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  INIT_CATS ; 
 int /*<<< orphan*/  MAX_CATNAME_LEN ; 
 int /*<<< orphan*/  MemSet (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ SPI_OK_FINISH ; 
 int SPI_OK_SELECT ; 
 int SPI_connect () ; 
 int SPI_execute (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SPI_finish () ; 
 char* SPI_getvalue (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ SPI_processed ; 
 TYPE_3__* SPI_tuptable ; 
 int /*<<< orphan*/  crosstab_HashTableInsert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * hash_create (char*,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static HTAB *
load_categories_hash(char *cats_sql, MemoryContext per_query_ctx)
{
	HTAB	   *crosstab_hash;
	HASHCTL		ctl;
	int			ret;
	uint64		proc;
	MemoryContext SPIcontext;

	/* initialize the category hash table */
	MemSet(&ctl, 0, sizeof(ctl));
	ctl.keysize = MAX_CATNAME_LEN;
	ctl.entrysize = sizeof(crosstab_HashEnt);
	ctl.hcxt = per_query_ctx;

	/*
	 * use INIT_CATS, defined above as a guess of how many hash table entries
	 * to create, initially
	 */
	crosstab_hash = hash_create("crosstab hash",
								INIT_CATS,
								&ctl,
								HASH_ELEM | HASH_CONTEXT);

	/* Connect to SPI manager */
	if ((ret = SPI_connect()) < 0)
		/* internal error */
		elog(ERROR, "load_categories_hash: SPI_connect returned %d", ret);

	/* Retrieve the category name rows */
	ret = SPI_execute(cats_sql, true, 0);
	proc = SPI_processed;

	/* Check for qualifying tuples */
	if ((ret == SPI_OK_SELECT) && (proc > 0))
	{
		SPITupleTable *spi_tuptable = SPI_tuptable;
		TupleDesc	spi_tupdesc = spi_tuptable->tupdesc;
		uint64		i;

		/*
		 * The provided categories SQL query must always return one column:
		 * category - the label or identifier for each column
		 */
		if (spi_tupdesc->natts != 1)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("provided \"categories\" SQL must " \
							"return 1 column of at least one row")));

		for (i = 0; i < proc; i++)
		{
			crosstab_cat_desc *catdesc;
			char	   *catname;
			HeapTuple	spi_tuple;

			/* get the next sql result tuple */
			spi_tuple = spi_tuptable->vals[i];

			/* get the category from the current sql result tuple */
			catname = SPI_getvalue(spi_tuple, spi_tupdesc, 1);

			SPIcontext = MemoryContextSwitchTo(per_query_ctx);

			catdesc = (crosstab_cat_desc *) palloc(sizeof(crosstab_cat_desc));
			catdesc->catname = catname;
			catdesc->attidx = i;

			/* Add the proc description block to the hashtable */
			crosstab_HashTableInsert(crosstab_hash, catdesc);

			MemoryContextSwitchTo(SPIcontext);
		}
	}

	if (SPI_finish() != SPI_OK_FINISH)
		/* internal error */
		elog(ERROR, "load_categories_hash: SPI_finish() failed");

	return crosstab_hash;
}
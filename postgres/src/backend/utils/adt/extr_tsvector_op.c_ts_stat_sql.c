#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  text ;
struct TYPE_12__ {int natts; } ;
struct TYPE_11__ {TYPE_6__* tupdesc; int /*<<< orphan*/ * vals; } ;
struct TYPE_10__ {int maxdepth; int weight; } ;
typedef  TYPE_1__ TSVectorStat ;
typedef  int /*<<< orphan*/ * SPIPlanPtr ;
typedef  int /*<<< orphan*/ * Portal ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsBinaryCoercible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_cursor_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPI_cursor_fetch (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * SPI_cursor_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SPI_freeplan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPI_freetuptable (TYPE_5__*) ; 
 int /*<<< orphan*/  SPI_getbinval (int /*<<< orphan*/ ,TYPE_6__*,int,int*) ; 
 int /*<<< orphan*/  SPI_gettypeid (TYPE_6__*,int) ; 
 int /*<<< orphan*/ * SPI_prepare (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SPI_processed ; 
 TYPE_5__* SPI_tuptable ; 
 int /*<<< orphan*/  TSVECTOROID ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pg_mblen (char*) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 
 TYPE_1__* ts_accum (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TSVectorStat *
ts_stat_sql(MemoryContext persistentContext, text *txt, text *ws)
{
	char	   *query = text_to_cstring(txt);
	TSVectorStat *stat;
	bool		isnull;
	Portal		portal;
	SPIPlanPtr	plan;

	if ((plan = SPI_prepare(query, 0, NULL)) == NULL)
		/* internal error */
		elog(ERROR, "SPI_prepare(\"%s\") failed", query);

	if ((portal = SPI_cursor_open(NULL, plan, NULL, NULL, true)) == NULL)
		/* internal error */
		elog(ERROR, "SPI_cursor_open(\"%s\") failed", query);

	SPI_cursor_fetch(portal, true, 100);

	if (SPI_tuptable == NULL ||
		SPI_tuptable->tupdesc->natts != 1 ||
		!IsBinaryCoercible(SPI_gettypeid(SPI_tuptable->tupdesc, 1),
						   TSVECTOROID))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("ts_stat query must return one tsvector column")));

	stat = MemoryContextAllocZero(persistentContext, sizeof(TSVectorStat));
	stat->maxdepth = 1;

	if (ws)
	{
		char	   *buf;

		buf = VARDATA_ANY(ws);
		while (buf - VARDATA_ANY(ws) < VARSIZE_ANY_EXHDR(ws))
		{
			if (pg_mblen(buf) == 1)
			{
				switch (*buf)
				{
					case 'A':
					case 'a':
						stat->weight |= 1 << 3;
						break;
					case 'B':
					case 'b':
						stat->weight |= 1 << 2;
						break;
					case 'C':
					case 'c':
						stat->weight |= 1 << 1;
						break;
					case 'D':
					case 'd':
						stat->weight |= 1;
						break;
					default:
						stat->weight |= 0;
				}
			}
			buf += pg_mblen(buf);
		}
	}

	while (SPI_processed > 0)
	{
		uint64		i;

		for (i = 0; i < SPI_processed; i++)
		{
			Datum		data = SPI_getbinval(SPI_tuptable->vals[i], SPI_tuptable->tupdesc, 1, &isnull);

			if (!isnull)
				stat = ts_accum(persistentContext, stat, data);
		}

		SPI_freetuptable(SPI_tuptable);
		SPI_cursor_fetch(portal, true, 100);
	}

	SPI_freetuptable(SPI_tuptable);
	SPI_cursor_close(portal);
	SPI_freeplan(plan);
	pfree(query);

	return stat;
}
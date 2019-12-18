#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_18__ {int /*<<< orphan*/  attname; scalar_t__ attisdropped; } ;
struct TYPE_17__ {TYPE_1__* rd_att; } ;
struct TYPE_16__ {int /*<<< orphan*/ * vals; } ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
struct TYPE_14__ {int natts; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  TYPE_3__ SPITupleTable ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_5__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_CARDINALITY_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int SPI_OK_SELECT ; 
 int SPI_connect () ; 
 int /*<<< orphan*/ * SPI_copytuple (int /*<<< orphan*/ ) ; 
 int SPI_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_finish () ; 
 int SPI_processed ; 
 TYPE_3__* SPI_tuptable ; 
 TYPE_5__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* generate_relation_name (TYPE_4__*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 char* quote_ident_cstr (int /*<<< orphan*/ ) ; 
 char* quote_literal_cstr (char*) ; 

__attribute__((used)) static HeapTuple
get_tuple_of_interest(Relation rel, int *pkattnums, int pknumatts, char **src_pkattvals)
{
	char	   *relname;
	TupleDesc	tupdesc;
	int			natts;
	StringInfoData buf;
	int			ret;
	HeapTuple	tuple;
	int			i;

	/*
	 * Connect to SPI manager
	 */
	if ((ret = SPI_connect()) < 0)
		/* internal error */
		elog(ERROR, "SPI connect failure - returned %d", ret);

	initStringInfo(&buf);

	/* get relation name including any needed schema prefix and quoting */
	relname = generate_relation_name(rel);

	tupdesc = rel->rd_att;
	natts = tupdesc->natts;

	/*
	 * Build sql statement to look up tuple of interest, ie, the one matching
	 * src_pkattvals.  We used to use "SELECT *" here, but it's simpler to
	 * generate a result tuple that matches the table's physical structure,
	 * with NULLs for any dropped columns.  Otherwise we have to deal with two
	 * different tupdescs and everything's very confusing.
	 */
	appendStringInfoString(&buf, "SELECT ");

	for (i = 0; i < natts; i++)
	{
		Form_pg_attribute attr = TupleDescAttr(tupdesc, i);

		if (i > 0)
			appendStringInfoString(&buf, ", ");

		if (attr->attisdropped)
			appendStringInfoString(&buf, "NULL");
		else
			appendStringInfoString(&buf,
								   quote_ident_cstr(NameStr(attr->attname)));
	}

	appendStringInfo(&buf, " FROM %s WHERE ", relname);

	for (i = 0; i < pknumatts; i++)
	{
		int			pkattnum = pkattnums[i];
		Form_pg_attribute attr = TupleDescAttr(tupdesc, pkattnum);

		if (i > 0)
			appendStringInfoString(&buf, " AND ");

		appendStringInfoString(&buf,
							   quote_ident_cstr(NameStr(attr->attname)));

		if (src_pkattvals[i] != NULL)
			appendStringInfo(&buf, " = %s",
							 quote_literal_cstr(src_pkattvals[i]));
		else
			appendStringInfoString(&buf, " IS NULL");
	}

	/*
	 * Retrieve the desired tuple
	 */
	ret = SPI_exec(buf.data, 0);
	pfree(buf.data);

	/*
	 * Only allow one qualifying tuple
	 */
	if ((ret == SPI_OK_SELECT) && (SPI_processed > 1))
		ereport(ERROR,
				(errcode(ERRCODE_CARDINALITY_VIOLATION),
				 errmsg("source criteria matched more than one record")));

	else if (ret == SPI_OK_SELECT && SPI_processed == 1)
	{
		SPITupleTable *tuptable = SPI_tuptable;

		tuple = SPI_copytuple(tuptable->vals[0]);
		SPI_finish();

		return tuple;
	}
	else
	{
		/*
		 * no qualifying tuples
		 */
		SPI_finish();

		return NULL;
	}

	/*
	 * never reached, but keep compiler quiet
	 */
	return NULL;
}
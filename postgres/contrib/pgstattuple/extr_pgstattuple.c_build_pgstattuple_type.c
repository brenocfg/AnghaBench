#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double table_len; double tuple_len; double dead_tuple_len; double free_space; double tuple_count; double dead_tuple_count; } ;
typedef  TYPE_1__ pgstattuple_type ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttInMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  BuildTupleFromCStrings (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 char* INT64_FORMAT ; 
 int NCHARS ; 
 int NCOLUMNS ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 int /*<<< orphan*/ * TupleDescGetAttInMetadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_call_result_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double) ; 

__attribute__((used)) static Datum
build_pgstattuple_type(pgstattuple_type *stat, FunctionCallInfo fcinfo)
{
#define NCOLUMNS	9
#define NCHARS		314

	HeapTuple	tuple;
	char	   *values[NCOLUMNS];
	char		values_buf[NCOLUMNS][NCHARS];
	int			i;
	double		tuple_percent;
	double		dead_tuple_percent;
	double		free_percent;	/* free/reusable space in % */
	TupleDesc	tupdesc;
	AttInMetadata *attinmeta;

	/* Build a tuple descriptor for our result type */
	if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE)
		elog(ERROR, "return type must be a row type");

	/*
	 * Generate attribute metadata needed later to produce tuples from raw C
	 * strings
	 */
	attinmeta = TupleDescGetAttInMetadata(tupdesc);

	if (stat->table_len == 0)
	{
		tuple_percent = 0.0;
		dead_tuple_percent = 0.0;
		free_percent = 0.0;
	}
	else
	{
		tuple_percent = 100.0 * stat->tuple_len / stat->table_len;
		dead_tuple_percent = 100.0 * stat->dead_tuple_len / stat->table_len;
		free_percent = 100.0 * stat->free_space / stat->table_len;
	}

	/*
	 * Prepare a values array for constructing the tuple. This should be an
	 * array of C strings which will be processed later by the appropriate
	 * "in" functions.
	 */
	for (i = 0; i < NCOLUMNS; i++)
		values[i] = values_buf[i];
	i = 0;
	snprintf(values[i++], NCHARS, INT64_FORMAT, stat->table_len);
	snprintf(values[i++], NCHARS, INT64_FORMAT, stat->tuple_count);
	snprintf(values[i++], NCHARS, INT64_FORMAT, stat->tuple_len);
	snprintf(values[i++], NCHARS, "%.2f", tuple_percent);
	snprintf(values[i++], NCHARS, INT64_FORMAT, stat->dead_tuple_count);
	snprintf(values[i++], NCHARS, INT64_FORMAT, stat->dead_tuple_len);
	snprintf(values[i++], NCHARS, "%.2f", dead_tuple_percent);
	snprintf(values[i++], NCHARS, INT64_FORMAT, stat->free_space);
	snprintf(values[i++], NCHARS, "%.2f", free_percent);

	/* build a tuple */
	tuple = BuildTupleFromCStrings(attinmeta, values);

	/* make the tuple into a datum */
	return HeapTupleGetDatum(tuple);
}
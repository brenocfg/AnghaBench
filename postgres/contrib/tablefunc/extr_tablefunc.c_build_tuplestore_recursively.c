#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_13__ {int /*<<< orphan*/  tupdesc; } ;
struct TYPE_12__ {int /*<<< orphan*/ * vals; int /*<<< orphan*/  tupdesc; } ;
struct TYPE_11__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ SPITupleTable ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ AttInMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  BuildTupleFromCStrings (TYPE_3__*,char**) ; 
 int CONNECTBY_NCOLS ; 
 int CONNECTBY_NCOLS_NOBRANCH ; 
 int /*<<< orphan*/  ERRCODE_INVALID_RECURSION ; 
 int /*<<< orphan*/  ERROR ; 
 int INT32_STRLEN ; 
 int SPI_OK_SELECT ; 
 int SPI_execute (char*,int,int /*<<< orphan*/ ) ; 
 char* SPI_getvalue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SPI_processed ; 
 TYPE_2__* SPI_tuptable ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  compatConnectbyTupleDescs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  quote_literal_cstr (char*) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  tuplestore_puttuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpfree (char*) ; 

__attribute__((used)) static void
build_tuplestore_recursively(char *key_fld,
							 char *parent_key_fld,
							 char *relname,
							 char *orderby_fld,
							 char *branch_delim,
							 char *start_with,
							 char *branch,
							 int level,
							 int *serial,
							 int max_depth,
							 bool show_branch,
							 bool show_serial,
							 MemoryContext per_query_ctx,
							 AttInMetadata *attinmeta,
							 Tuplestorestate *tupstore)
{
	TupleDesc	tupdesc = attinmeta->tupdesc;
	int			ret;
	uint64		proc;
	int			serial_column;
	StringInfoData sql;
	char	  **values;
	char	   *current_key;
	char	   *current_key_parent;
	char		current_level[INT32_STRLEN];
	char		serial_str[INT32_STRLEN];
	char	   *current_branch;
	HeapTuple	tuple;

	if (max_depth > 0 && level > max_depth)
		return;

	initStringInfo(&sql);

	/* Build initial sql statement */
	if (!show_serial)
	{
		appendStringInfo(&sql, "SELECT %s, %s FROM %s WHERE %s = %s AND %s IS NOT NULL AND %s <> %s",
						 key_fld,
						 parent_key_fld,
						 relname,
						 parent_key_fld,
						 quote_literal_cstr(start_with),
						 key_fld, key_fld, parent_key_fld);
		serial_column = 0;
	}
	else
	{
		appendStringInfo(&sql, "SELECT %s, %s FROM %s WHERE %s = %s AND %s IS NOT NULL AND %s <> %s ORDER BY %s",
						 key_fld,
						 parent_key_fld,
						 relname,
						 parent_key_fld,
						 quote_literal_cstr(start_with),
						 key_fld, key_fld, parent_key_fld,
						 orderby_fld);
		serial_column = 1;
	}

	if (show_branch)
		values = (char **) palloc((CONNECTBY_NCOLS + serial_column) * sizeof(char *));
	else
		values = (char **) palloc((CONNECTBY_NCOLS_NOBRANCH + serial_column) * sizeof(char *));

	/* First time through, do a little setup */
	if (level == 0)
	{
		/* root value is the one we initially start with */
		values[0] = start_with;

		/* root value has no parent */
		values[1] = NULL;

		/* root level is 0 */
		sprintf(current_level, "%d", level);
		values[2] = current_level;

		/* root branch is just starting root value */
		if (show_branch)
			values[3] = start_with;

		/* root starts the serial with 1 */
		if (show_serial)
		{
			sprintf(serial_str, "%d", (*serial)++);
			if (show_branch)
				values[4] = serial_str;
			else
				values[3] = serial_str;
		}

		/* construct the tuple */
		tuple = BuildTupleFromCStrings(attinmeta, values);

		/* now store it */
		tuplestore_puttuple(tupstore, tuple);

		/* increment level */
		level++;
	}

	/* Retrieve the desired rows */
	ret = SPI_execute(sql.data, true, 0);
	proc = SPI_processed;

	/* Check for qualifying tuples */
	if ((ret == SPI_OK_SELECT) && (proc > 0))
	{
		HeapTuple	spi_tuple;
		SPITupleTable *tuptable = SPI_tuptable;
		TupleDesc	spi_tupdesc = tuptable->tupdesc;
		uint64		i;
		StringInfoData branchstr;
		StringInfoData chk_branchstr;
		StringInfoData chk_current_key;

		/*
		 * Check that return tupdesc is compatible with the one we got from
		 * the query.
		 */
		compatConnectbyTupleDescs(tupdesc, spi_tupdesc);

		initStringInfo(&branchstr);
		initStringInfo(&chk_branchstr);
		initStringInfo(&chk_current_key);

		for (i = 0; i < proc; i++)
		{
			/* initialize branch for this pass */
			appendStringInfoString(&branchstr, branch);
			appendStringInfo(&chk_branchstr, "%s%s%s", branch_delim, branch, branch_delim);

			/* get the next sql result tuple */
			spi_tuple = tuptable->vals[i];

			/* get the current key (might be NULL) */
			current_key = SPI_getvalue(spi_tuple, spi_tupdesc, 1);

			/* get the parent key (might be NULL) */
			current_key_parent = SPI_getvalue(spi_tuple, spi_tupdesc, 2);

			/* get the current level */
			sprintf(current_level, "%d", level);

			/* check to see if this key is also an ancestor */
			if (current_key)
			{
				appendStringInfo(&chk_current_key, "%s%s%s",
								 branch_delim, current_key, branch_delim);
				if (strstr(chk_branchstr.data, chk_current_key.data))
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_RECURSION),
							 errmsg("infinite recursion detected")));
			}

			/* OK, extend the branch */
			if (current_key)
				appendStringInfo(&branchstr, "%s%s", branch_delim, current_key);
			current_branch = branchstr.data;

			/* build a tuple */
			values[0] = current_key;
			values[1] = current_key_parent;
			values[2] = current_level;
			if (show_branch)
				values[3] = current_branch;
			if (show_serial)
			{
				sprintf(serial_str, "%d", (*serial)++);
				if (show_branch)
					values[4] = serial_str;
				else
					values[3] = serial_str;
			}

			tuple = BuildTupleFromCStrings(attinmeta, values);

			/* store the tuple for later use */
			tuplestore_puttuple(tupstore, tuple);

			heap_freetuple(tuple);

			/* recurse using current_key as the new start_with */
			if (current_key)
				build_tuplestore_recursively(key_fld,
											 parent_key_fld,
											 relname,
											 orderby_fld,
											 branch_delim,
											 current_key,
											 current_branch,
											 level + 1,
											 serial,
											 max_depth,
											 show_branch,
											 show_serial,
											 per_query_ctx,
											 attinmeta,
											 tupstore);

			xpfree(current_key);
			xpfree(current_key_parent);

			/* reset branch for next pass */
			resetStringInfo(&branchstr);
			resetStringInfo(&chk_branchstr);
			resetStringInfo(&chk_current_key);
		}

		xpfree(branchstr.data);
		xpfree(chk_branchstr.data);
		xpfree(chk_current_key.data);
	}
}
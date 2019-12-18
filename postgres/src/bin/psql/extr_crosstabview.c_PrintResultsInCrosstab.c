#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pivot_field ;
struct TYPE_7__ {int count; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ avl_tree ;
struct TYPE_8__ {int /*<<< orphan*/ ** ctv_args; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int CROSSTABVIEW_MAX_COLUMNS ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/  const*,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/  const*,int,int) ; 
 int PQnfields (int /*<<< orphan*/  const*) ; 
 int PQntuples (int /*<<< orphan*/  const*) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  avlCollectFields (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avlFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avlInit (TYPE_1__*) ; 
 int /*<<< orphan*/  avlMergeValue (TYPE_1__*,char*,char*) ; 
 int indexOfColumn (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 scalar_t__ pg_malloc (int) ; 
 int printCrosstab (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int) ; 
 TYPE_2__ pset ; 
 int /*<<< orphan*/  rankSort (int,int /*<<< orphan*/ *) ; 

bool
PrintResultsInCrosstab(const PGresult *res)
{
	bool		retval = false;
	avl_tree	piv_columns;
	avl_tree	piv_rows;
	pivot_field *array_columns = NULL;
	pivot_field *array_rows = NULL;
	int			num_columns = 0;
	int			num_rows = 0;
	int			field_for_rows;
	int			field_for_columns;
	int			field_for_data;
	int			sort_field_for_columns;
	int			rn;

	avlInit(&piv_rows);
	avlInit(&piv_columns);

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		pg_log_error("\\crosstabview: statement did not return a result set");
		goto error_return;
	}

	if (PQnfields(res) < 3)
	{
		pg_log_error("\\crosstabview: query must return at least three columns");
		goto error_return;
	}

	/* Process first optional arg (vertical header column) */
	if (pset.ctv_args[0] == NULL)
		field_for_rows = 0;
	else
	{
		field_for_rows = indexOfColumn(pset.ctv_args[0], res);
		if (field_for_rows < 0)
			goto error_return;
	}

	/* Process second optional arg (horizontal header column) */
	if (pset.ctv_args[1] == NULL)
		field_for_columns = 1;
	else
	{
		field_for_columns = indexOfColumn(pset.ctv_args[1], res);
		if (field_for_columns < 0)
			goto error_return;
	}

	/* Insist that header columns be distinct */
	if (field_for_columns == field_for_rows)
	{
		pg_log_error("\\crosstabview: vertical and horizontal headers must be different columns");
		goto error_return;
	}

	/* Process third optional arg (data column) */
	if (pset.ctv_args[2] == NULL)
	{
		int			i;

		/*
		 * If the data column was not specified, we search for the one not
		 * used as either vertical or horizontal headers.  Must be exactly
		 * three columns, or this won't be unique.
		 */
		if (PQnfields(res) != 3)
		{
			pg_log_error("\\crosstabview: data column must be specified when query returns more than three columns");
			goto error_return;
		}

		field_for_data = -1;
		for (i = 0; i < PQnfields(res); i++)
		{
			if (i != field_for_rows && i != field_for_columns)
			{
				field_for_data = i;
				break;
			}
		}
		Assert(field_for_data >= 0);
	}
	else
	{
		field_for_data = indexOfColumn(pset.ctv_args[2], res);
		if (field_for_data < 0)
			goto error_return;
	}

	/* Process fourth optional arg (horizontal header sort column) */
	if (pset.ctv_args[3] == NULL)
		sort_field_for_columns = -1;	/* no sort column */
	else
	{
		sort_field_for_columns = indexOfColumn(pset.ctv_args[3], res);
		if (sort_field_for_columns < 0)
			goto error_return;
	}

	/*
	 * First part: accumulate the names that go into the vertical and
	 * horizontal headers, each into an AVL binary tree to build the set of
	 * DISTINCT values.
	 */

	for (rn = 0; rn < PQntuples(res); rn++)
	{
		char	   *val;
		char	   *val1;

		/* horizontal */
		val = PQgetisnull(res, rn, field_for_columns) ? NULL :
			PQgetvalue(res, rn, field_for_columns);
		val1 = NULL;

		if (sort_field_for_columns >= 0 &&
			!PQgetisnull(res, rn, sort_field_for_columns))
			val1 = PQgetvalue(res, rn, sort_field_for_columns);

		avlMergeValue(&piv_columns, val, val1);

		if (piv_columns.count > CROSSTABVIEW_MAX_COLUMNS)
		{
			pg_log_error("\\crosstabview: maximum number of columns (%d) exceeded",
						 CROSSTABVIEW_MAX_COLUMNS);
			goto error_return;
		}

		/* vertical */
		val = PQgetisnull(res, rn, field_for_rows) ? NULL :
			PQgetvalue(res, rn, field_for_rows);

		avlMergeValue(&piv_rows, val, NULL);
	}

	/*
	 * Second part: Generate sorted arrays from the AVL trees.
	 */

	num_columns = piv_columns.count;
	num_rows = piv_rows.count;

	array_columns = (pivot_field *)
		pg_malloc(sizeof(pivot_field) * num_columns);

	array_rows = (pivot_field *)
		pg_malloc(sizeof(pivot_field) * num_rows);

	avlCollectFields(&piv_columns, piv_columns.root, array_columns, 0);
	avlCollectFields(&piv_rows, piv_rows.root, array_rows, 0);

	/*
	 * Third part: optionally, process the ranking data for the horizontal
	 * header
	 */
	if (sort_field_for_columns >= 0)
		rankSort(num_columns, array_columns);

	/*
	 * Fourth part: print the crosstab'ed results.
	 */
	retval = printCrosstab(res,
						   num_columns, array_columns, field_for_columns,
						   num_rows, array_rows, field_for_rows,
						   field_for_data);

error_return:
	avlFree(&piv_columns, piv_columns.root);
	avlFree(&piv_rows, piv_rows.root);
	pg_free(array_columns);
	pg_free(array_rows);

	return retval;
}
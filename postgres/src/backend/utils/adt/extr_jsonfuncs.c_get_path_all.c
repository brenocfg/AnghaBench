#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 long INT_MAX ; 
 long INT_MIN ; 
 int /*<<< orphan*/ * PG_GETARG_ARRAYTYPE_P (int) ; 
 int /*<<< orphan*/ * PG_GETARG_TEXT_PP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_NULL () ; 
 int /*<<< orphan*/  PG_RETURN_TEXT_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXTOID ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 scalar_t__ array_contains_nulls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char,int /*<<< orphan*/ **,int**,int*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * get_worker (int /*<<< orphan*/ *,char**,int*,int,int) ; 
 void* palloc (int) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static Datum
get_path_all(FunctionCallInfo fcinfo, bool as_text)
{
	text	   *json = PG_GETARG_TEXT_PP(0);
	ArrayType  *path = PG_GETARG_ARRAYTYPE_P(1);
	text	   *result;
	Datum	   *pathtext;
	bool	   *pathnulls;
	int			npath;
	char	  **tpath;
	int		   *ipath;
	int			i;

	/*
	 * If the array contains any null elements, return NULL, on the grounds
	 * that you'd have gotten NULL if any RHS value were NULL in a nested
	 * series of applications of the -> operator.  (Note: because we also
	 * return NULL for error cases such as no-such-field, this is true
	 * regardless of the contents of the rest of the array.)
	 */
	if (array_contains_nulls(path))
		PG_RETURN_NULL();

	deconstruct_array(path, TEXTOID, -1, false, 'i',
					  &pathtext, &pathnulls, &npath);

	tpath = palloc(npath * sizeof(char *));
	ipath = palloc(npath * sizeof(int));

	for (i = 0; i < npath; i++)
	{
		Assert(!pathnulls[i]);
		tpath[i] = TextDatumGetCString(pathtext[i]);

		/*
		 * we have no idea at this stage what structure the document is so
		 * just convert anything in the path that we can to an integer and set
		 * all the other integers to INT_MIN which will never match.
		 */
		if (*tpath[i] != '\0')
		{
			long		ind;
			char	   *endptr;

			errno = 0;
			ind = strtol(tpath[i], &endptr, 10);
			if (*endptr == '\0' && errno == 0 && ind <= INT_MAX && ind >= INT_MIN)
				ipath[i] = (int) ind;
			else
				ipath[i] = INT_MIN;
		}
		else
			ipath[i] = INT_MIN;
	}

	result = get_worker(json, tpath, ipath, npath, as_text);

	if (result != NULL)
		PG_RETURN_TEXT_P(result);
	else
		PG_RETURN_NULL();
}
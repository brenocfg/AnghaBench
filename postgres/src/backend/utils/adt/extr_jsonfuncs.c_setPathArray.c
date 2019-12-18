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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  scalar_t__ JsonbIteratorToken ;
typedef  int /*<<< orphan*/  JsonbIterator ;
typedef  int /*<<< orphan*/  Jsonb ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 long INT_MAX ; 
 long INT_MIN ; 
 int JB_PATH_CREATE ; 
 int JB_PATH_CREATE_OR_INSERT ; 
 int JB_PATH_INSERT_AFTER ; 
 int JB_PATH_INSERT_BEFORE ; 
 int JB_PATH_REPLACE ; 
 scalar_t__ JsonbIteratorNext (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 scalar_t__ WJB_BEGIN_ARRAY ; 
 scalar_t__ WJB_BEGIN_OBJECT ; 
 scalar_t__ WJB_END_ARRAY ; 
 scalar_t__ WJB_END_OBJECT ; 
 int /*<<< orphan*/  addJsonbToParseState (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pushJsonbValue (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setPath (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static void
setPathArray(JsonbIterator **it, Datum *path_elems, bool *path_nulls,
			 int path_len, JsonbParseState **st, int level,
			 Jsonb *newval, uint32 nelems, int op_type)
{
	JsonbValue	v;
	int			idx,
				i;
	bool		done = false;

	/* pick correct index */
	if (level < path_len && !path_nulls[level])
	{
		char	   *c = TextDatumGetCString(path_elems[level]);
		long		lindex;
		char	   *badp;

		errno = 0;
		lindex = strtol(c, &badp, 10);
		if (errno != 0 || badp == c || *badp != '\0' || lindex > INT_MAX ||
			lindex < INT_MIN)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("path element at position %d is not an integer: \"%s\"",
							level + 1, c)));
		idx = lindex;
	}
	else
		idx = nelems;

	if (idx < 0)
	{
		if (-idx > nelems)
			idx = INT_MIN;
		else
			idx = nelems + idx;
	}

	if (idx > 0 && idx > nelems)
		idx = nelems;

	/*
	 * if we're creating, and idx == INT_MIN, we prepend the new value to the
	 * array also if the array is empty - in which case we don't really care
	 * what the idx value is
	 */

	if ((idx == INT_MIN || nelems == 0) && (level == path_len - 1) &&
		(op_type & JB_PATH_CREATE_OR_INSERT))
	{
		Assert(newval != NULL);
		addJsonbToParseState(st, newval);
		done = true;
	}

	/* iterate over the array elements */
	for (i = 0; i < nelems; i++)
	{
		JsonbIteratorToken r;

		if (i == idx && level < path_len)
		{
			if (level == path_len - 1)
			{
				r = JsonbIteratorNext(it, &v, true);	/* skip */

				if (op_type & (JB_PATH_INSERT_BEFORE | JB_PATH_CREATE))
					addJsonbToParseState(st, newval);

				/*
				 * We should keep current value only in case of
				 * JB_PATH_INSERT_BEFORE or JB_PATH_INSERT_AFTER because
				 * otherwise it should be deleted or replaced
				 */
				if (op_type & (JB_PATH_INSERT_AFTER | JB_PATH_INSERT_BEFORE))
					(void) pushJsonbValue(st, r, &v);

				if (op_type & (JB_PATH_INSERT_AFTER | JB_PATH_REPLACE))
					addJsonbToParseState(st, newval);

				done = true;
			}
			else
				(void) setPath(it, path_elems, path_nulls, path_len,
							   st, level + 1, newval, op_type);
		}
		else
		{
			r = JsonbIteratorNext(it, &v, false);

			(void) pushJsonbValue(st, r, r < WJB_BEGIN_ARRAY ? &v : NULL);

			if (r == WJB_BEGIN_ARRAY || r == WJB_BEGIN_OBJECT)
			{
				int			walking_level = 1;

				while (walking_level != 0)
				{
					r = JsonbIteratorNext(it, &v, false);

					if (r == WJB_BEGIN_ARRAY || r == WJB_BEGIN_OBJECT)
						++walking_level;
					if (r == WJB_END_ARRAY || r == WJB_END_OBJECT)
						--walking_level;

					(void) pushJsonbValue(st, r, r < WJB_BEGIN_ARRAY ? &v : NULL);
				}
			}

			if ((op_type & JB_PATH_CREATE_OR_INSERT) && !done &&
				level == path_len - 1 && i == nelems - 1)
			{
				addJsonbToParseState(st, newval);
			}
		}
	}
}
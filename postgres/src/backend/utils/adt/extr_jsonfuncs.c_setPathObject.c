#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_6__ {scalar_t__ len; void* val; } ;
struct TYPE_7__ {TYPE_1__ string; } ;
struct TYPE_8__ {TYPE_2__ val; void* type; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  scalar_t__ JsonbIteratorToken ;
typedef  int /*<<< orphan*/  JsonbIterator ;
typedef  int /*<<< orphan*/  Jsonb ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int JB_PATH_CREATE_OR_INSERT ; 
 int JB_PATH_DELETE ; 
 int JB_PATH_INSERT_AFTER ; 
 int JB_PATH_INSERT_BEFORE ; 
 scalar_t__ JsonbIteratorNext (int /*<<< orphan*/ **,TYPE_3__*,int) ; 
 void* VARDATA_ANY (int /*<<< orphan*/ ) ; 
 scalar_t__ VARSIZE_ANY_EXHDR (int /*<<< orphan*/ ) ; 
 scalar_t__ WJB_BEGIN_ARRAY ; 
 scalar_t__ WJB_BEGIN_OBJECT ; 
 scalar_t__ WJB_END_ARRAY ; 
 scalar_t__ WJB_END_OBJECT ; 
 scalar_t__ WJB_KEY ; 
 int /*<<< orphan*/  addJsonbToParseState (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 void* jbvString ; 
 scalar_t__ memcmp (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  pushJsonbValue (int /*<<< orphan*/ **,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  setPath (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
setPathObject(JsonbIterator **it, Datum *path_elems, bool *path_nulls,
			  int path_len, JsonbParseState **st, int level,
			  Jsonb *newval, uint32 npairs, int op_type)
{
	JsonbValue	v;
	int			i;
	JsonbValue	k;
	bool		done = false;

	if (level >= path_len || path_nulls[level])
		done = true;

	/* empty object is a special case for create */
	if ((npairs == 0) && (op_type & JB_PATH_CREATE_OR_INSERT) &&
		(level == path_len - 1))
	{
		JsonbValue	newkey;

		newkey.type = jbvString;
		newkey.val.string.len = VARSIZE_ANY_EXHDR(path_elems[level]);
		newkey.val.string.val = VARDATA_ANY(path_elems[level]);

		(void) pushJsonbValue(st, WJB_KEY, &newkey);
		addJsonbToParseState(st, newval);
	}

	for (i = 0; i < npairs; i++)
	{
		JsonbIteratorToken r = JsonbIteratorNext(it, &k, true);

		Assert(r == WJB_KEY);

		if (!done &&
			k.val.string.len == VARSIZE_ANY_EXHDR(path_elems[level]) &&
			memcmp(k.val.string.val, VARDATA_ANY(path_elems[level]),
				   k.val.string.len) == 0)
		{
			if (level == path_len - 1)
			{
				/*
				 * called from jsonb_insert(), it forbids redefining an
				 * existing value
				 */
				if (op_type & (JB_PATH_INSERT_BEFORE | JB_PATH_INSERT_AFTER))
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("cannot replace existing key"),
							 errhint("Try using the function jsonb_set "
									 "to replace key value.")));

				r = JsonbIteratorNext(it, &v, true);	/* skip value */
				if (!(op_type & JB_PATH_DELETE))
				{
					(void) pushJsonbValue(st, WJB_KEY, &k);
					addJsonbToParseState(st, newval);
				}
				done = true;
			}
			else
			{
				(void) pushJsonbValue(st, r, &k);
				setPath(it, path_elems, path_nulls, path_len,
						st, level + 1, newval, op_type);
			}
		}
		else
		{
			if ((op_type & JB_PATH_CREATE_OR_INSERT) && !done &&
				level == path_len - 1 && i == npairs - 1)
			{
				JsonbValue	newkey;

				newkey.type = jbvString;
				newkey.val.string.len = VARSIZE_ANY_EXHDR(path_elems[level]);
				newkey.val.string.val = VARDATA_ANY(path_elems[level]);

				(void) pushJsonbValue(st, WJB_KEY, &newkey);
				addJsonbToParseState(st, newval);
			}

			(void) pushJsonbValue(st, r, &k);
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
		}
	}
}
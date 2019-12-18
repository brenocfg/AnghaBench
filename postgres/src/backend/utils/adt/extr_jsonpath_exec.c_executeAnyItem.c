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
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ int32 ;
struct TYPE_13__ {int ignoreStructuralErrors; } ;
struct TYPE_10__ {int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {TYPE_1__ binary; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_2__ val; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbIterator ;
typedef  int /*<<< orphan*/  JsonbContainer ;
typedef  int /*<<< orphan*/  JsonValueList ;
typedef  int /*<<< orphan*/  JsonPathItem ;
typedef  scalar_t__ JsonPathExecResult ;
typedef  TYPE_4__ JsonPathExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  JsonValueListAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * JsonbIteratorInit (int /*<<< orphan*/ *) ; 
 scalar_t__ JsonbIteratorNext (int /*<<< orphan*/ **,TYPE_3__*,int) ; 
 scalar_t__ PG_UINT32_MAX ; 
 scalar_t__ WJB_DONE ; 
 scalar_t__ WJB_ELEM ; 
 scalar_t__ WJB_KEY ; 
 scalar_t__ WJB_VALUE ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  copyJsonbValue (TYPE_3__*) ; 
 scalar_t__ executeItemOptUnwrapTarget (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ jbvBinary ; 
 scalar_t__ jperIsError (scalar_t__) ; 
 scalar_t__ jperNotFound ; 
 scalar_t__ jperOk ; 

__attribute__((used)) static JsonPathExecResult
executeAnyItem(JsonPathExecContext *cxt, JsonPathItem *jsp, JsonbContainer *jbc,
			   JsonValueList *found, uint32 level, uint32 first, uint32 last,
			   bool ignoreStructuralErrors, bool unwrapNext)
{
	JsonPathExecResult res = jperNotFound;
	JsonbIterator *it;
	int32		r;
	JsonbValue	v;

	check_stack_depth();

	if (level > last)
		return res;

	it = JsonbIteratorInit(jbc);

	/*
	 * Recursively iterate over jsonb objects/arrays
	 */
	while ((r = JsonbIteratorNext(&it, &v, true)) != WJB_DONE)
	{
		if (r == WJB_KEY)
		{
			r = JsonbIteratorNext(&it, &v, true);
			Assert(r == WJB_VALUE);
		}

		if (r == WJB_VALUE || r == WJB_ELEM)
		{

			if (level >= first ||
				(first == PG_UINT32_MAX && last == PG_UINT32_MAX &&
				 v.type != jbvBinary))	/* leaves only requested */
			{
				/* check expression */
				if (jsp)
				{
					if (ignoreStructuralErrors)
					{
						bool		savedIgnoreStructuralErrors;

						savedIgnoreStructuralErrors = cxt->ignoreStructuralErrors;
						cxt->ignoreStructuralErrors = true;
						res = executeItemOptUnwrapTarget(cxt, jsp, &v, found, unwrapNext);
						cxt->ignoreStructuralErrors = savedIgnoreStructuralErrors;
					}
					else
						res = executeItemOptUnwrapTarget(cxt, jsp, &v, found, unwrapNext);

					if (jperIsError(res))
						break;

					if (res == jperOk && !found)
						break;
				}
				else if (found)
					JsonValueListAppend(found, copyJsonbValue(&v));
				else
					return jperOk;
			}

			if (level < last && v.type == jbvBinary)
			{
				res = executeAnyItem
					(cxt, jsp, v.val.binary.data, found,
					 level + 1, first, last,
					 ignoreStructuralErrors, unwrapNext);

				if (jperIsError(res))
					break;

				if (res == jperOk && found == NULL)
					break;
			}
		}
	}

	return res;
}
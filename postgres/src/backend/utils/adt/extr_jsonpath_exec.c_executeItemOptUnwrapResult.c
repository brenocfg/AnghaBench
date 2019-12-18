#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {scalar_t__ type; } ;
typedef  TYPE_1__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonValueListIterator ;
typedef  TYPE_2__ JsonValueList ;
typedef  int /*<<< orphan*/  JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecResult ;
typedef  int /*<<< orphan*/  JsonPathExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  JsonValueListAppend (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  JsonValueListInitIterator (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* JsonValueListNext (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ JsonbType (TYPE_1__*) ; 
 int /*<<< orphan*/  executeItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  executeItemUnwrapTargetArray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int) ; 
 scalar_t__ jbvArray ; 
 scalar_t__ jperIsError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jperOk ; 
 scalar_t__ jspAutoUnwrap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static JsonPathExecResult
executeItemOptUnwrapResult(JsonPathExecContext *cxt, JsonPathItem *jsp,
						   JsonbValue *jb, bool unwrap,
						   JsonValueList *found)
{
	if (unwrap && jspAutoUnwrap(cxt))
	{
		JsonValueList seq = {0};
		JsonValueListIterator it;
		JsonPathExecResult res = executeItem(cxt, jsp, jb, &seq);
		JsonbValue *item;

		if (jperIsError(res))
			return res;

		JsonValueListInitIterator(&seq, &it);
		while ((item = JsonValueListNext(&seq, &it)))
		{
			Assert(item->type != jbvArray);

			if (JsonbType(item) == jbvArray)
				executeItemUnwrapTargetArray(cxt, NULL, item, found, false);
			else
				JsonValueListAppend(found, item);
		}

		return jperOk;
	}

	return executeItem(cxt, jsp, jb, found);
}
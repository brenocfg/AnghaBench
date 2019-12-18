#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int boolean; } ;
struct TYPE_5__ {TYPE_1__ val; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonValueList ;
typedef  int /*<<< orphan*/  JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecResult ;
typedef  int /*<<< orphan*/  JsonPathExecContext ;
typedef  scalar_t__ JsonPathBool ;

/* Variables and functions */
 int /*<<< orphan*/  executeNextItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jbvBool ; 
 int /*<<< orphan*/  jbvNull ; 
 scalar_t__ jpbTrue ; 
 scalar_t__ jpbUnknown ; 
 int /*<<< orphan*/  jperOk ; 
 int /*<<< orphan*/  jspGetNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static JsonPathExecResult
appendBoolResult(JsonPathExecContext *cxt, JsonPathItem *jsp,
				 JsonValueList *found, JsonPathBool res)
{
	JsonPathItem next;
	JsonbValue	jbv;

	if (!jspGetNext(jsp, &next) && !found)
		return jperOk;			/* found singleton boolean value */

	if (res == jpbUnknown)
	{
		jbv.type = jbvNull;
	}
	else
	{
		jbv.type = jbvBool;
		jbv.val.boolean = res == jpbTrue;
	}

	return executeNextItem(cxt, jsp, &next, &jbv, found, true);
}
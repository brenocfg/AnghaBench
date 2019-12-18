#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__ binary; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ val; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonValueList ;
typedef  int /*<<< orphan*/  JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecResult ;
typedef  int /*<<< orphan*/  JsonPathExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  executeAnyItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 scalar_t__ jbvArray ; 
 scalar_t__ jbvBinary ; 

__attribute__((used)) static JsonPathExecResult
executeItemUnwrapTargetArray(JsonPathExecContext *cxt, JsonPathItem *jsp,
							 JsonbValue *jb, JsonValueList *found,
							 bool unwrapElements)
{
	if (jb->type != jbvBinary)
	{
		Assert(jb->type != jbvArray);
		elog(ERROR, "invalid jsonb array value type: %d", jb->type);
	}

	return executeAnyItem
		(cxt, jsp, jb->val.binary.data, found, 1, 1, 1,
		 false, unwrapElements);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int throwErrors; } ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  int /*<<< orphan*/  JsonValueList ;
typedef  int /*<<< orphan*/  JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecResult ;
typedef  TYPE_1__ JsonPathExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  executeItemOptUnwrapResult (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static JsonPathExecResult
executeItemOptUnwrapResultNoThrow(JsonPathExecContext *cxt,
								  JsonPathItem *jsp,
								  JsonbValue *jb, bool unwrap,
								  JsonValueList *found)
{
	JsonPathExecResult res;
	bool		throwErrors = cxt->throwErrors;

	cxt->throwErrors = false;
	res = executeItemOptUnwrapResult(cxt, jsp, jb, unwrap, found);
	cxt->throwErrors = throwErrors;

	return res;
}
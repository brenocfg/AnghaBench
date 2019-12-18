#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ JsonbValue ;
typedef  int /*<<< orphan*/  JEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsAJsonbScalar (TYPE_1__*) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  convertJsonbArray (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  convertJsonbObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  convertJsonbScalar (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jbvArray ; 
 scalar_t__ jbvObject ; 

__attribute__((used)) static void
convertJsonbValue(StringInfo buffer, JEntry *header, JsonbValue *val, int level)
{
	check_stack_depth();

	if (!val)
		return;

	/*
	 * A JsonbValue passed as val should never have a type of jbvBinary, and
	 * neither should any of its sub-components. Those values will be produced
	 * by convertJsonbArray and convertJsonbObject, the results of which will
	 * not be passed back to this function as an argument.
	 */

	if (IsAJsonbScalar(val))
		convertJsonbScalar(buffer, header, val);
	else if (val->type == jbvArray)
		convertJsonbArray(buffer, header, val, level);
	else if (val->type == jbvObject)
		convertJsonbObject(buffer, header, val, level);
	else
		elog(ERROR, "unknown type of jsonb container to convert");
}
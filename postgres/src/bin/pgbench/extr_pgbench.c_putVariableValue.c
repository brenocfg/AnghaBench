#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/ * svalue; } ;
typedef  TYPE_1__ Variable ;
typedef  int /*<<< orphan*/  PgBenchValue ;
typedef  int /*<<< orphan*/  CState ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupCreateVariable (int /*<<< orphan*/ *,char const*,char*) ; 

__attribute__((used)) static bool
putVariableValue(CState *st, const char *context, char *name,
				 const PgBenchValue *value)
{
	Variable   *var;

	var = lookupCreateVariable(st, context, name);
	if (!var)
		return false;

	if (var->svalue)
		free(var->svalue);
	var->svalue = NULL;
	var->value = *value;

	return true;
}
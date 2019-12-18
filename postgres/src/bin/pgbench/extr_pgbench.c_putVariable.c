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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {char* svalue; TYPE_1__ value; } ;
typedef  TYPE_2__ Variable ;
typedef  int /*<<< orphan*/  CState ;

/* Variables and functions */
 int /*<<< orphan*/  PGBT_NO_VALUE ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* lookupCreateVariable (int /*<<< orphan*/ *,char const*,char*) ; 
 char* pg_strdup (char const*) ; 

__attribute__((used)) static bool
putVariable(CState *st, const char *context, char *name, const char *value)
{
	Variable   *var;
	char	   *val;

	var = lookupCreateVariable(st, context, name);
	if (!var)
		return false;

	/* dup then free, in case value is pointing at this variable */
	val = pg_strdup(value);

	if (var->svalue)
		free(var->svalue);
	var->svalue = val;
	var->value.type = PGBT_NO_VALUE;

	return true;
}
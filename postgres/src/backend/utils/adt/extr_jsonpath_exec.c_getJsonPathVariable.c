#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ type; } ;
struct TYPE_19__ {int /*<<< orphan*/  root; } ;
struct TYPE_16__ {char* val; int len; } ;
struct TYPE_17__ {TYPE_1__ string; } ;
struct TYPE_18__ {TYPE_2__ val; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  TYPE_4__ Jsonb ;
typedef  TYPE_5__ JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  JB_FOBJECT ; 
 int /*<<< orphan*/  JsonbInitBinary (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* findJsonbValueFromContainer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  jbvNull ; 
 int /*<<< orphan*/  jbvString ; 
 scalar_t__ jpiVariable ; 
 char* jspGetString (TYPE_5__*,int*) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 int /*<<< orphan*/  pnstrdup (char*,int) ; 
 int /*<<< orphan*/  setBaseObject (int /*<<< orphan*/ *,TYPE_3__*,int) ; 

__attribute__((used)) static void
getJsonPathVariable(JsonPathExecContext *cxt, JsonPathItem *variable,
					Jsonb *vars, JsonbValue *value)
{
	char	   *varName;
	int			varNameLength;
	JsonbValue	tmp;
	JsonbValue *v;

	if (!vars)
	{
		value->type = jbvNull;
		return;
	}

	Assert(variable->type == jpiVariable);
	varName = jspGetString(variable, &varNameLength);
	tmp.type = jbvString;
	tmp.val.string.val = varName;
	tmp.val.string.len = varNameLength;

	v = findJsonbValueFromContainer(&vars->root, JB_FOBJECT, &tmp);

	if (v)
	{
		*value = *v;
		pfree(v);
	}
	else
	{
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("could not find jsonpath variable \"%s\"",
						pnstrdup(varName, varNameLength))));
	}

	JsonbInitBinary(&tmp, vars);
	setBaseObject(cxt, &tmp, 1);
}
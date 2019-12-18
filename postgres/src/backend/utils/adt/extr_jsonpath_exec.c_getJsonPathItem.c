#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  vars; } ;
struct TYPE_18__ {int type; } ;
struct TYPE_15__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_16__ {TYPE_1__ string; int /*<<< orphan*/  numeric; int /*<<< orphan*/  boolean; } ;
struct TYPE_17__ {TYPE_2__ val; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  TYPE_4__ JsonPathItem ;
typedef  TYPE_5__ JsonPathExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getJsonPathVariable (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  jbvBool ; 
 int /*<<< orphan*/  jbvNull ; 
 int /*<<< orphan*/  jbvNumeric ; 
 int /*<<< orphan*/  jbvString ; 
#define  jpiBool 132 
#define  jpiNull 131 
#define  jpiNumeric 130 
#define  jpiString 129 
#define  jpiVariable 128 
 int /*<<< orphan*/  jspGetBool (TYPE_4__*) ; 
 int /*<<< orphan*/  jspGetNumeric (TYPE_4__*) ; 
 int /*<<< orphan*/  jspGetString (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
getJsonPathItem(JsonPathExecContext *cxt, JsonPathItem *item,
				JsonbValue *value)
{
	switch (item->type)
	{
		case jpiNull:
			value->type = jbvNull;
			break;
		case jpiBool:
			value->type = jbvBool;
			value->val.boolean = jspGetBool(item);
			break;
		case jpiNumeric:
			value->type = jbvNumeric;
			value->val.numeric = jspGetNumeric(item);
			break;
		case jpiString:
			value->type = jbvString;
			value->val.string.val = jspGetString(item,
												 &value->val.string.len);
			break;
		case jpiVariable:
			getJsonPathVariable(cxt, item, cxt->vars, value);
			return;
		default:
			elog(ERROR, "unexpected jsonpath item type");
	}
}
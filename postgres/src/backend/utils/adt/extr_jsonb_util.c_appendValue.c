#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  nPairs; TYPE_1__* pairs; } ;
struct TYPE_10__ {TYPE_2__ object; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_3__ val; } ;
struct TYPE_12__ {TYPE_4__ contVal; } ;
struct TYPE_8__ {TYPE_4__ value; } ;
typedef  TYPE_4__ JsonbValue ;
typedef  TYPE_5__ JsonbParseState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ jbvObject ; 

__attribute__((used)) static void
appendValue(JsonbParseState *pstate, JsonbValue *scalarVal)
{
	JsonbValue *object = &pstate->contVal;

	Assert(object->type == jbvObject);

	object->val.object.pairs[object->val.object.nPairs++].value = *scalarVal;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  nextPos; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ JsonPathItem ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ jpiAbs ; 
 scalar_t__ jpiAdd ; 
 scalar_t__ jpiAnd ; 
 scalar_t__ jpiAny ; 
 scalar_t__ jpiAnyArray ; 
 scalar_t__ jpiAnyKey ; 
 scalar_t__ jpiBool ; 
 scalar_t__ jpiCeiling ; 
 scalar_t__ jpiCurrent ; 
 scalar_t__ jpiDatetime ; 
 scalar_t__ jpiDiv ; 
 scalar_t__ jpiDouble ; 
 scalar_t__ jpiEqual ; 
 scalar_t__ jpiExists ; 
 scalar_t__ jpiFilter ; 
 scalar_t__ jpiFloor ; 
 scalar_t__ jpiGreater ; 
 scalar_t__ jpiGreaterOrEqual ; 
 scalar_t__ jpiIndexArray ; 
 scalar_t__ jpiIsUnknown ; 
 scalar_t__ jpiKey ; 
 scalar_t__ jpiKeyValue ; 
 scalar_t__ jpiLast ; 
 scalar_t__ jpiLess ; 
 scalar_t__ jpiLessOrEqual ; 
 scalar_t__ jpiMinus ; 
 scalar_t__ jpiMod ; 
 scalar_t__ jpiMul ; 
 scalar_t__ jpiNot ; 
 scalar_t__ jpiNotEqual ; 
 scalar_t__ jpiNull ; 
 scalar_t__ jpiNumeric ; 
 scalar_t__ jpiOr ; 
 scalar_t__ jpiPlus ; 
 scalar_t__ jpiRoot ; 
 scalar_t__ jpiSize ; 
 scalar_t__ jpiStartsWith ; 
 scalar_t__ jpiString ; 
 scalar_t__ jpiSub ; 
 scalar_t__ jpiType ; 
 scalar_t__ jpiVariable ; 
 scalar_t__ jspHasNext (TYPE_1__*) ; 
 int /*<<< orphan*/  jspInitByBuffer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
jspGetNext(JsonPathItem *v, JsonPathItem *a)
{
	if (jspHasNext(v))
	{
		Assert(v->type == jpiString ||
			   v->type == jpiNumeric ||
			   v->type == jpiBool ||
			   v->type == jpiNull ||
			   v->type == jpiKey ||
			   v->type == jpiAny ||
			   v->type == jpiAnyArray ||
			   v->type == jpiAnyKey ||
			   v->type == jpiIndexArray ||
			   v->type == jpiFilter ||
			   v->type == jpiCurrent ||
			   v->type == jpiExists ||
			   v->type == jpiRoot ||
			   v->type == jpiVariable ||
			   v->type == jpiLast ||
			   v->type == jpiAdd ||
			   v->type == jpiSub ||
			   v->type == jpiMul ||
			   v->type == jpiDiv ||
			   v->type == jpiMod ||
			   v->type == jpiPlus ||
			   v->type == jpiMinus ||
			   v->type == jpiEqual ||
			   v->type == jpiNotEqual ||
			   v->type == jpiGreater ||
			   v->type == jpiGreaterOrEqual ||
			   v->type == jpiLess ||
			   v->type == jpiLessOrEqual ||
			   v->type == jpiAnd ||
			   v->type == jpiOr ||
			   v->type == jpiNot ||
			   v->type == jpiIsUnknown ||
			   v->type == jpiType ||
			   v->type == jpiSize ||
			   v->type == jpiAbs ||
			   v->type == jpiFloor ||
			   v->type == jpiCeiling ||
			   v->type == jpiDouble ||
			   v->type == jpiDatetime ||
			   v->type == jpiKeyValue ||
			   v->type == jpiStartsWith);

		if (a)
			jspInitByBuffer(a, v->base, v->nextPos);
		return true;
	}

	return false;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  left; } ;
struct TYPE_8__ {TYPE_1__ args; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_2__ content; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ JsonPathItem ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ jpiAdd ; 
 scalar_t__ jpiAnd ; 
 scalar_t__ jpiDiv ; 
 scalar_t__ jpiEqual ; 
 scalar_t__ jpiGreater ; 
 scalar_t__ jpiGreaterOrEqual ; 
 scalar_t__ jpiLess ; 
 scalar_t__ jpiLessOrEqual ; 
 scalar_t__ jpiMod ; 
 scalar_t__ jpiMul ; 
 scalar_t__ jpiNotEqual ; 
 scalar_t__ jpiOr ; 
 scalar_t__ jpiStartsWith ; 
 scalar_t__ jpiSub ; 
 int /*<<< orphan*/  jspInitByBuffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
jspGetLeftArg(JsonPathItem *v, JsonPathItem *a)
{
	Assert(v->type == jpiAnd ||
		   v->type == jpiOr ||
		   v->type == jpiEqual ||
		   v->type == jpiNotEqual ||
		   v->type == jpiLess ||
		   v->type == jpiGreater ||
		   v->type == jpiLessOrEqual ||
		   v->type == jpiGreaterOrEqual ||
		   v->type == jpiAdd ||
		   v->type == jpiSub ||
		   v->type == jpiMul ||
		   v->type == jpiDiv ||
		   v->type == jpiMod ||
		   v->type == jpiStartsWith);

	jspInitByBuffer(a, v->base, v->content.args.left);
}
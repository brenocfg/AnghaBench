#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  arg; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ content; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ JsonPathItem ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ jpiDatetime ; 
 scalar_t__ jpiExists ; 
 scalar_t__ jpiFilter ; 
 scalar_t__ jpiIsUnknown ; 
 scalar_t__ jpiMinus ; 
 scalar_t__ jpiNot ; 
 scalar_t__ jpiPlus ; 
 int /*<<< orphan*/  jspInitByBuffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
jspGetArg(JsonPathItem *v, JsonPathItem *a)
{
	Assert(v->type == jpiFilter ||
		   v->type == jpiNot ||
		   v->type == jpiIsUnknown ||
		   v->type == jpiExists ||
		   v->type == jpiPlus ||
		   v->type == jpiMinus ||
		   v->type == jpiDatetime);

	jspInitByBuffer(a, v->base, v->content.arg);
}
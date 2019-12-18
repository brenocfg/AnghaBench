#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* elems; } ;
struct TYPE_10__ {TYPE_1__ array; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_2__ content; int /*<<< orphan*/  base; } ;
struct TYPE_11__ {int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
typedef  TYPE_4__ JsonPathItem ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ jpiIndexArray ; 
 int /*<<< orphan*/  jspInitByBuffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
jspGetArraySubscript(JsonPathItem *v, JsonPathItem *from, JsonPathItem *to,
					 int i)
{
	Assert(v->type == jpiIndexArray);

	jspInitByBuffer(from, v->base, v->content.array.elems[i].from);

	if (!v->content.array.elems[i].to)
		return false;

	jspInitByBuffer(to, v->base, v->content.array.elems[i].to);

	return true;
}
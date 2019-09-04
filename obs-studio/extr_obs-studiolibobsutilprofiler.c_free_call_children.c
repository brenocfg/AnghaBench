#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num; TYPE_1__* array; } ;
struct TYPE_4__ {TYPE_3__ children; } ;
typedef  TYPE_1__ profile_call ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_3__) ; 

__attribute__((used)) static void free_call_children(profile_call *call)
{
	if (!call)
		return;

	const size_t num = call->children.num;
	for (size_t i = 0; i < num; i++)
		free_call_children(&call->children.array[i]);

	da_free(call->children);
}
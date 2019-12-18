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
struct TYPE_3__ {int /*<<< orphan*/ * ob_type; } ;
typedef  TYPE_1__ PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PLy_PlanType ; 

bool
is_PLyPlanObject(PyObject *ob)
{
	return ob->ob_type == &PLy_PlanType;
}
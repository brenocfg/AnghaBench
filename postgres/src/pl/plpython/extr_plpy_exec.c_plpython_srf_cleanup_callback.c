#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * savedargs; int /*<<< orphan*/ * iter; } ;
typedef  TYPE_1__ PLySRFState ;

/* Variables and functions */
 int /*<<< orphan*/  PLy_function_drop_args (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
plpython_srf_cleanup_callback(void *arg)
{
	PLySRFState *srfstate = (PLySRFState *) arg;

	/* Release refcount on the iter, if we still have one */
	Py_XDECREF(srfstate->iter);
	srfstate->iter = NULL;
	/* And drop any saved args; we won't need them */
	if (srfstate->savedargs)
		PLy_function_drop_args(srfstate->savedargs);
	srfstate->savedargs = NULL;
}
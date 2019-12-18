#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* func ) (TYPE_1__*,int /*<<< orphan*/ *,int*,int) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PLyObToDatum ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int*,int) ; 

Datum
PLy_output_convert(PLyObToDatum *arg, PyObject *val, bool *isnull)
{
	/* at outer level, we are not considering an array element */
	return arg->func(arg, val, isnull, false);
}
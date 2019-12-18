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
struct TYPE_2__ {int /*<<< orphan*/  rows; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PLyResultObject ;

/* Variables and functions */
 int PyObject_SetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
PLy_result_ass_subscript(PyObject *arg, PyObject *item, PyObject *value)
{
	PLyResultObject *ob = (PLyResultObject *) arg;

	return PyObject_SetItem(ob->rows, item, value);
}
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
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PLyResultObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyList_Size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Py_ssize_t
PLy_result_length(PyObject *arg)
{
	PLyResultObject *ob = (PLyResultObject *) arg;

	return PyList_Size(ob->rows);
}
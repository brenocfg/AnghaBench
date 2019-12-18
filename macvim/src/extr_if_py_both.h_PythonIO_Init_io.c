#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error ; 
 int /*<<< orphan*/  Output ; 
 scalar_t__ PyErr_Occurred () ; 
 scalar_t__ PySys_SetObject (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 

__attribute__((used)) static int
PythonIO_Init_io(void)
{
    if (PySys_SetObject("stdout", (PyObject *)(void *)&Output))
	return -1;
    if (PySys_SetObject("stderr", (PyObject *)(void *)&Error))
	return -1;

    if (PyErr_Occurred())
    {
	EMSG(_("E264: Python: Error initialising I/O objects"));
	return -1;
    }

    return 0;
}
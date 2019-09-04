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
struct TYPE_3__ {int flags; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayFlagsObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ARRAY_ALIGNED ; 
 int /*<<< orphan*/  NPY_ARRAY_C_CONTIGUOUS ; 
 int /*<<< orphan*/  NPY_ARRAY_F_CONTIGUOUS ; 
 int /*<<< orphan*/  NPY_ARRAY_OWNDATA ; 
 int /*<<< orphan*/  NPY_ARRAY_UPDATEIFCOPY ; 
 int /*<<< orphan*/  NPY_ARRAY_WRITEABLE ; 
 int /*<<< orphan*/  NPY_ARRAY_WRITEBACKIFCOPY ; 
 int /*<<< orphan*/ * PyUString_FromFormat (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _torf_ (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
arrayflags_print(PyArrayFlagsObject *self)
{
    int fl = self->flags;

    return PyUString_FromFormat(
                        "  %s : %s\n  %s : %s\n"
                        "  %s : %s\n  %s : %s\n"
                        "  %s : %s\n  %s : %s\n"
                        "  %s : %s",
                        "C_CONTIGUOUS",    _torf_(fl, NPY_ARRAY_C_CONTIGUOUS),
                        "F_CONTIGUOUS",    _torf_(fl, NPY_ARRAY_F_CONTIGUOUS),
                        "OWNDATA",         _torf_(fl, NPY_ARRAY_OWNDATA),
                        "WRITEABLE",       _torf_(fl, NPY_ARRAY_WRITEABLE),
                        "ALIGNED",         _torf_(fl, NPY_ARRAY_ALIGNED),
                        "WRITEBACKIFCOPY", _torf_(fl, NPY_ARRAY_WRITEBACKIFCOPY),
                        "UPDATEIFCOPY",    _torf_(fl, NPY_ARRAY_UPDATEIFCOPY));
}
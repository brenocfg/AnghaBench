#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ml_line_count; } ;
struct TYPE_8__ {TYPE_1__ b_ml; } ;
struct TYPE_7__ {TYPE_4__* buf; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int PyInt ;
typedef  TYPE_2__ BufferObject ;

/* Variables and functions */
 scalar_t__ CheckBuffer (TYPE_2__*) ; 
 scalar_t__ FAIL ; 
 scalar_t__ InsertBufferLines (TYPE_4__*,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 

__attribute__((used)) static PyObject *
RBAppend(
	BufferObject *self,
	PyObject *args,
	PyInt start,
	PyInt end,
	PyInt *new_end)
{
    PyObject *lines;
    PyInt len_change;
    PyInt max;
    PyInt n;

    if (CheckBuffer(self))
	return NULL;

    if (end == -1)
	end = self->buf->b_ml.ml_line_count;

    max = n = end - start + 1;

    if (!PyArg_ParseTuple(args, "O|n", &lines, &n))
	return NULL;

    if (n < 0 || n > max)
    {
	PyErr_SET_STRING(PyExc_IndexError, N_("line number out of range"));
	return NULL;
    }

    if (InsertBufferLines(self->buf, n + start - 1, lines, &len_change) == FAIL)
	return NULL;

    if (new_end)
	*new_end = end + len_change;

    Py_INCREF(Py_None);
    return Py_None;
}
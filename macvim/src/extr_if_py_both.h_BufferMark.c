#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ lnum; scalar_t__ col; } ;
typedef  TYPE_1__ pos_T ;
typedef  char char_u ;
typedef  int /*<<< orphan*/  buf_T ;
struct TYPE_7__ {int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ BufferObject ;

/* Variables and functions */
 scalar_t__ CheckBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SET_VIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,long,long) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 char* StringToChars (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ VimTryEnd () ; 
 int /*<<< orphan*/  VimTryStart () ; 
 TYPE_1__* getmark (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switch_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
BufferMark(BufferObject *self, PyObject *pmarkObject)
{
    pos_T	*posp;
    char_u	*pmark;
    char_u	mark;
    buf_T	*savebuf;
    PyObject	*todecref;

    if (CheckBuffer(self))
	return NULL;

    if (!(pmark = StringToChars(pmarkObject, &todecref)))
	return NULL;

    if (pmark[0] == '\0' || pmark[1] != '\0')
    {
	PyErr_SET_STRING(PyExc_ValueError,
		N_("mark name must be a single character"));
	Py_XDECREF(todecref);
	return NULL;
    }

    mark = *pmark;

    Py_XDECREF(todecref);

    VimTryStart();
    switch_buffer(&savebuf, self->buf);
    posp = getmark(mark, FALSE);
    restore_buffer(savebuf);
    if (VimTryEnd())
	return NULL;

    if (posp == NULL)
    {
	PyErr_SET_VIM(N_("invalid mark name"));
	return NULL;
    }

    if (posp->lnum <= 0)
    {
	/* Or raise an error? */
	Py_INCREF(Py_None);
	return Py_None;
    }

    return Py_BuildValue("(ll)", (long)(posp->lnum), (long)(posp->col));
}
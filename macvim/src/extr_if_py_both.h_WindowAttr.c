#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ col; scalar_t__ lnum; } ;
typedef  TYPE_1__ pos_T ;
typedef  int /*<<< orphan*/  checkfun ;
struct TYPE_9__ {scalar_t__ tabObject; TYPE_3__* win; } ;
typedef  TYPE_2__ WindowObject ;
struct TYPE_10__ {int /*<<< orphan*/  w_vars; scalar_t__ w_winrow; scalar_t__ w_height; TYPE_1__ w_cursor; int /*<<< orphan*/  w_buffer; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ BufferNew (int /*<<< orphan*/ ) ; 
 scalar_t__ CheckTabPage (scalar_t__) ; 
 scalar_t__ CheckWindow ; 
 int /*<<< orphan*/ * NEW_DICTIONARY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ObjectDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OptionsNew (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromLong (long) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,long,long) ; 
 int /*<<< orphan*/  Py_INCREF (scalar_t__) ; 
 int /*<<< orphan*/  SREQ_WIN ; 
 scalar_t__ W_WIDTH (TYPE_3__*) ; 
 scalar_t__ W_WINCOL (TYPE_3__*) ; 
 int /*<<< orphan*/  WindowAttrs ; 
 int /*<<< orphan*/  get_firstwin (scalar_t__) ; 
 scalar_t__ get_win_number (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static PyObject *
WindowAttr(WindowObject *self, char *name)
{
    if (strcmp(name, "buffer") == 0)
	return (PyObject *)BufferNew(self->win->w_buffer);
    else if (strcmp(name, "cursor") == 0)
    {
	pos_T *pos = &self->win->w_cursor;

	return Py_BuildValue("(ll)", (long)(pos->lnum), (long)(pos->col));
    }
    else if (strcmp(name, "height") == 0)
	return PyLong_FromLong((long)(self->win->w_height));
#ifdef FEAT_WINDOWS
    else if (strcmp(name, "row") == 0)
	return PyLong_FromLong((long)(self->win->w_winrow));
#endif
#ifdef FEAT_VERTSPLIT
    else if (strcmp(name, "width") == 0)
	return PyLong_FromLong((long)(W_WIDTH(self->win)));
    else if (strcmp(name, "col") == 0)
	return PyLong_FromLong((long)(W_WINCOL(self->win)));
#endif
    else if (strcmp(name, "vars") == 0)
	return NEW_DICTIONARY(self->win->w_vars);
    else if (strcmp(name, "options") == 0)
	return OptionsNew(SREQ_WIN, self->win, (checkfun) CheckWindow,
			(PyObject *) self);
    else if (strcmp(name, "number") == 0)
    {
	if (CheckTabPage(self->tabObject))
	    return NULL;
	return PyLong_FromLong((long)
		get_win_number(self->win, get_firstwin(self->tabObject)));
    }
    else if (strcmp(name, "tabpage") == 0)
    {
	Py_INCREF(self->tabObject);
	return (PyObject *)(self->tabObject);
    }
    else if (strcmp(name, "__members__") == 0)
	return ObjectDir(NULL, WindowAttrs);
    else
	return NULL;
}
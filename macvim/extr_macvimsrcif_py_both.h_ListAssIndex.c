#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  typval_T ;
struct TYPE_13__ {int /*<<< orphan*/  li_tv; } ;
typedef  TYPE_1__ listitem_T ;
struct TYPE_14__ {scalar_t__ lv_lock; } ;
typedef  TYPE_2__ list_T ;
struct TYPE_15__ {TYPE_2__* list; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ ListObject ;

/* Variables and functions */
 int ConvertFromPyObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FAIL ; 
 scalar_t__ ListLength (TYPE_3__*) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SET_VIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 int /*<<< orphan*/  RAISE_LOCKED_LIST ; 
 int /*<<< orphan*/  clear_tv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_tv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_append_tv (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* list_find (TYPE_2__*,long) ; 
 int /*<<< orphan*/  vim_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vimlist_remove (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int
ListAssIndex(ListObject *self, Py_ssize_t index, PyObject *obj)
{
    typval_T	tv;
    list_T	*l = self->list;
    listitem_T	*li;
    Py_ssize_t	length = ListLength(self);

    if (l->lv_lock)
    {
	RAISE_LOCKED_LIST;
	return -1;
    }
    if (index > length || (index == length && obj == NULL))
    {
	PyErr_SET_STRING(PyExc_IndexError, N_("list index out of range"));
	return -1;
    }

    if (obj == NULL)
    {
	li = list_find(l, (long) index);
	vimlist_remove(l, li, li);
	clear_tv(&li->li_tv);
	vim_free(li);
	return 0;
    }

    if (ConvertFromPyObject(obj, &tv) == -1)
	return -1;

    if (index == length)
    {
	if (list_append_tv(l, &tv) == FAIL)
	{
	    clear_tv(&tv);
	    PyErr_SET_VIM(N_("failed to add item to list"));
	    return -1;
	}
    }
    else
    {
	li = list_find(l, (long) index);
	clear_tv(&li->li_tv);
	copy_tv(&tv, &li->li_tv);
	clear_tv(&tv);
    }
    return 0;
}
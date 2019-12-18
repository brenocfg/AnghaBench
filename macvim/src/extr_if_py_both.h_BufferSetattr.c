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
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  aco_save_T ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ BufferObject ;

/* Variables and functions */
 scalar_t__ CheckBuffer (TYPE_1__*) ; 
 int FAIL ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_SET_VIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * StringToChars (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ VimTryEnd () ; 
 int /*<<< orphan*/  VimTryStart () ; 
 int /*<<< orphan*/  aucmd_prepbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aucmd_restbuf (int /*<<< orphan*/ *) ; 
 int rename_buffer (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
BufferSetattr(BufferObject *self, char *name, PyObject *valObject)
{
    if (CheckBuffer(self))
	return -1;

    if (strcmp(name, "name") == 0)
    {
	char_u		*val;
	aco_save_T	aco;
	int		ren_ret;
	PyObject	*todecref;

	if (!(val = StringToChars(valObject, &todecref)))
	    return -1;

	VimTryStart();
	/* Using aucmd_*: autocommands will be executed by rename_buffer */
	aucmd_prepbuf(&aco, self->buf);
	ren_ret = rename_buffer(val);
	aucmd_restbuf(&aco);
	Py_XDECREF(todecref);
	if (VimTryEnd())
	    return -1;

	if (ren_ret == FAIL)
	{
	    PyErr_SET_VIM(N_("failed to rename buffer"));
	    return -1;
	}
	return 0;
    }
    else
    {
	PyErr_SetString(PyExc_AttributeError, name);
	return -1;
    }
}
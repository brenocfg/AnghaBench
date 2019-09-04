#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_6__ {int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {scalar_t__ (* tp_alloc ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ FunctionObject ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOLOAD_CHAR ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_FORMAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  func_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_expanded_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  translated_function_exists (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vim_strsave (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
FunctionNew(PyTypeObject *subtype, char_u *name)
{
    FunctionObject	*self;

    self = (FunctionObject *) subtype->tp_alloc(subtype, 0);

    if (self == NULL)
	return NULL;

    if (isdigit(*name))
    {
	if (!translated_function_exists(name))
	{
	    PyErr_FORMAT(PyExc_ValueError,
		    N_("unnamed function %s does not exist"), name);
	    return NULL;
	}
	self->name = vim_strsave(name);
	func_ref(self->name);
    }
    else
	if ((self->name = get_expanded_name(name,
				    vim_strchr(name, AUTOLOAD_CHAR) == NULL))
		== NULL)
	{
	    PyErr_FORMAT(PyExc_ValueError,
		    N_("function %s does not exist"), name);
	    return NULL;
	}

    return (PyObject *)(self);
}
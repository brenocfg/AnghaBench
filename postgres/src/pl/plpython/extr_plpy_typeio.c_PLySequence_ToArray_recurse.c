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
struct TYPE_4__ {int /*<<< orphan*/  (* func ) (TYPE_1__*,int /*<<< orphan*/ *,int*,int) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PLyObToDatum ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,int) ; 
 int PySequence_Length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
PLySequence_ToArray_recurse(PLyObToDatum *elm, PyObject *list,
							int *dims, int ndim, int dim,
							Datum *elems, bool *nulls, int *currelem)
{
	int			i;

	if (PySequence_Length(list) != dims[dim])
		ereport(ERROR,
				(errmsg("wrong length of inner sequence: has length %d, but %d was expected",
						(int) PySequence_Length(list), dims[dim]),
				 (errdetail("To construct a multidimensional array, the inner sequences must all have the same length."))));

	if (dim < ndim - 1)
	{
		for (i = 0; i < dims[dim]; i++)
		{
			PyObject   *sublist = PySequence_GetItem(list, i);

			PLySequence_ToArray_recurse(elm, sublist, dims, ndim, dim + 1,
										elems, nulls, currelem);
			Py_XDECREF(sublist);
		}
	}
	else
	{
		for (i = 0; i < dims[dim]; i++)
		{
			PyObject   *obj = PySequence_GetItem(list, i);

			elems[*currelem] = elm->func(elm, obj, &nulls[*currelem], true);
			Py_XDECREF(obj);
			(*currelem)++;
		}
	}
}
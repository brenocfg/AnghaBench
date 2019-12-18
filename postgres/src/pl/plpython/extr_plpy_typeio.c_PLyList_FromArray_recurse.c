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
typedef  int bits8 ;
struct TYPE_4__ {int /*<<< orphan*/  typalign; int /*<<< orphan*/  typlen; int /*<<< orphan*/ * (* func ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  typbyval; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PLyDatumToOb ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * PyList_New (int) ; 
 int /*<<< orphan*/  PyList_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 char* att_addlength_pointer (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ att_align_nominal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_att (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
PLyList_FromArray_recurse(PLyDatumToOb *elm, int *dims, int ndim, int dim,
						  char **dataptr_p, bits8 **bitmap_p, int *bitmask_p)
{
	int			i;
	PyObject   *list;

	list = PyList_New(dims[dim]);
	if (!list)
		return NULL;

	if (dim < ndim - 1)
	{
		/* Outer dimension. Recurse for each inner slice. */
		for (i = 0; i < dims[dim]; i++)
		{
			PyObject   *sublist;

			sublist = PLyList_FromArray_recurse(elm, dims, ndim, dim + 1,
												dataptr_p, bitmap_p, bitmask_p);
			PyList_SET_ITEM(list, i, sublist);
		}
	}
	else
	{
		/*
		 * Innermost dimension. Fill the list with the values from the array
		 * for this slice.
		 */
		char	   *dataptr = *dataptr_p;
		bits8	   *bitmap = *bitmap_p;
		int			bitmask = *bitmask_p;

		for (i = 0; i < dims[dim]; i++)
		{
			/* checking for NULL */
			if (bitmap && (*bitmap & bitmask) == 0)
			{
				Py_INCREF(Py_None);
				PyList_SET_ITEM(list, i, Py_None);
			}
			else
			{
				Datum		itemvalue;

				itemvalue = fetch_att(dataptr, elm->typbyval, elm->typlen);
				PyList_SET_ITEM(list, i, elm->func(elm, itemvalue));
				dataptr = att_addlength_pointer(dataptr, elm->typlen, dataptr);
				dataptr = (char *) att_align_nominal(dataptr, elm->typalign);
			}

			/* advance bitmap pointer if any */
			if (bitmap)
			{
				bitmask <<= 1;
				if (bitmask == 0x100 /* (1<<8) */ )
				{
					bitmap++;
					bitmask = 1;
				}
			}
		}

		*dataptr_p = dataptr;
		*bitmap_p = bitmap;
		*bitmask_p = bitmask;
	}

	return list;
}
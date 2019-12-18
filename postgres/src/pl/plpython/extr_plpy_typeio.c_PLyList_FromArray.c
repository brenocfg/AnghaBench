#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bits8 ;
struct TYPE_6__ {TYPE_3__* elm; } ;
struct TYPE_7__ {TYPE_1__ array; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ PLyDatumToOb ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 char* ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ARR_NULLBITMAP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int MAXDIM ; 
 int /*<<< orphan*/ * PLyList_FromArray_recurse (TYPE_3__*,int*,int,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/ * PyList_New (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
PLyList_FromArray(PLyDatumToOb *arg, Datum d)
{
	ArrayType  *array = DatumGetArrayTypeP(d);
	PLyDatumToOb *elm = arg->u.array.elm;
	int			ndim;
	int		   *dims;
	char	   *dataptr;
	bits8	   *bitmap;
	int			bitmask;

	if (ARR_NDIM(array) == 0)
		return PyList_New(0);

	/* Array dimensions and left bounds */
	ndim = ARR_NDIM(array);
	dims = ARR_DIMS(array);
	Assert(ndim < MAXDIM);

	/*
	 * We iterate the SQL array in the physical order it's stored in the
	 * datum. For example, for a 3-dimensional array the order of iteration
	 * would be the following: [0,0,0] elements through [0,0,k], then [0,1,0]
	 * through [0,1,k] till [0,m,k], then [1,0,0] through [1,0,k] till
	 * [1,m,k], and so on.
	 *
	 * In Python, there are no multi-dimensional lists as such, but they are
	 * represented as a list of lists. So a 3-d array of [n,m,k] elements is a
	 * list of n m-element arrays, each element of which is k-element array.
	 * PLyList_FromArray_recurse() builds the Python list for a single
	 * dimension, and recurses for the next inner dimension.
	 */
	dataptr = ARR_DATA_PTR(array);
	bitmap = ARR_NULLBITMAP(array);
	bitmask = 1;

	return PLyList_FromArray_recurse(elm, dims, ndim, 0,
									 &dataptr, &bitmap, &bitmask);
}
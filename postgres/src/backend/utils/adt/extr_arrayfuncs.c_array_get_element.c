#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bits8 ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 char* ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 int* ARR_LBOUND (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ARR_NULLBITMAP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ArrayCast (char*,int,int) ; 
 int ArrayGetOffset (int,int*,int*,int*) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int MAXDIM ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED (scalar_t__) ; 
 int /*<<< orphan*/  array_get_element_expanded (int /*<<< orphan*/ ,int,int*,int,int,int,char,int*) ; 
 scalar_t__ array_get_isnull (int /*<<< orphan*/ *,int) ; 
 char* array_seek (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,char) ; 

Datum
array_get_element(Datum arraydatum,
				  int nSubscripts,
				  int *indx,
				  int arraytyplen,
				  int elmlen,
				  bool elmbyval,
				  char elmalign,
				  bool *isNull)
{
	int			i,
				ndim,
			   *dim,
			   *lb,
				offset,
				fixedDim[1],
				fixedLb[1];
	char	   *arraydataptr,
			   *retptr;
	bits8	   *arraynullsptr;

	if (arraytyplen > 0)
	{
		/*
		 * fixed-length arrays -- these are assumed to be 1-d, 0-based
		 */
		ndim = 1;
		fixedDim[0] = arraytyplen / elmlen;
		fixedLb[0] = 0;
		dim = fixedDim;
		lb = fixedLb;
		arraydataptr = (char *) DatumGetPointer(arraydatum);
		arraynullsptr = NULL;
	}
	else if (VARATT_IS_EXTERNAL_EXPANDED(DatumGetPointer(arraydatum)))
	{
		/* expanded array: let's do this in a separate function */
		return array_get_element_expanded(arraydatum,
										  nSubscripts,
										  indx,
										  arraytyplen,
										  elmlen,
										  elmbyval,
										  elmalign,
										  isNull);
	}
	else
	{
		/* detoast array if necessary, producing normal varlena input */
		ArrayType  *array = DatumGetArrayTypeP(arraydatum);

		ndim = ARR_NDIM(array);
		dim = ARR_DIMS(array);
		lb = ARR_LBOUND(array);
		arraydataptr = ARR_DATA_PTR(array);
		arraynullsptr = ARR_NULLBITMAP(array);
	}

	/*
	 * Return NULL for invalid subscript
	 */
	if (ndim != nSubscripts || ndim <= 0 || ndim > MAXDIM)
	{
		*isNull = true;
		return (Datum) 0;
	}
	for (i = 0; i < ndim; i++)
	{
		if (indx[i] < lb[i] || indx[i] >= (dim[i] + lb[i]))
		{
			*isNull = true;
			return (Datum) 0;
		}
	}

	/*
	 * Calculate the element number
	 */
	offset = ArrayGetOffset(nSubscripts, dim, lb, indx);

	/*
	 * Check for NULL array element
	 */
	if (array_get_isnull(arraynullsptr, offset))
	{
		*isNull = true;
		return (Datum) 0;
	}

	/*
	 * OK, get the element
	 */
	*isNull = false;
	retptr = array_seek(arraydataptr, 0, arraynullsptr, offset,
						elmlen, elmbyval, elmalign);
	return ArrayCast(retptr, elmbyval, elmlen);
}
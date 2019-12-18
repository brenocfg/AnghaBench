#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ea_magic; int typlen; int typbyval; char typalign; int ndims; int* dims; int* lbound; int* dnulls; int /*<<< orphan*/ * dvalues; } ;
typedef  TYPE_1__ ExpandedArrayHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int ArrayGetOffset (int,int*,int*,int*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetEOHP (int /*<<< orphan*/ ) ; 
 scalar_t__ EA_MAGIC ; 
 int MAXDIM ; 
 int /*<<< orphan*/  deconstruct_expanded_array (TYPE_1__*) ; 

__attribute__((used)) static Datum
array_get_element_expanded(Datum arraydatum,
						   int nSubscripts, int *indx,
						   int arraytyplen,
						   int elmlen, bool elmbyval, char elmalign,
						   bool *isNull)
{
	ExpandedArrayHeader *eah;
	int			i,
				ndim,
			   *dim,
			   *lb,
				offset;
	Datum	   *dvalues;
	bool	   *dnulls;

	eah = (ExpandedArrayHeader *) DatumGetEOHP(arraydatum);
	Assert(eah->ea_magic == EA_MAGIC);

	/* sanity-check caller's info against object */
	Assert(arraytyplen == -1);
	Assert(elmlen == eah->typlen);
	Assert(elmbyval == eah->typbyval);
	Assert(elmalign == eah->typalign);

	ndim = eah->ndims;
	dim = eah->dims;
	lb = eah->lbound;

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
	 * Deconstruct array if we didn't already.  Note that we apply this even
	 * if the input is nominally read-only: it should be safe enough.
	 */
	deconstruct_expanded_array(eah);

	dvalues = eah->dvalues;
	dnulls = eah->dnulls;

	/*
	 * Check for NULL array element
	 */
	if (dnulls && dnulls[offset])
	{
		*isNull = true;
		return (Datum) 0;
	}

	/*
	 * OK, get the element.  It's OK to return a pass-by-ref value as a
	 * pointer into the expanded array, for the same reason that regular
	 * array_get_element can return a pointer into flat arrays: the value is
	 * assumed not to change for as long as the Datum reference can exist.
	 */
	*isNull = false;
	return dvalues[offset];
}
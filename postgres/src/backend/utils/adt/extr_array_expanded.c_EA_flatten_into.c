#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_9__ {int ndim; int /*<<< orphan*/  elemtype; scalar_t__ dataoffset; } ;
struct TYPE_8__ {scalar_t__ ea_magic; scalar_t__ flat_size; int nelems; int ndims; int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; scalar_t__ dnulls; int /*<<< orphan*/  dvalues; scalar_t__ lbound; scalar_t__ dims; int /*<<< orphan*/  element_type; scalar_t__ fvalue; } ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  ExpandedObjectHeader ;
typedef  TYPE_1__ ExpandedArrayHeader ;
typedef  TYPE_2__ ArrayType ;

/* Variables and functions */
 void* ARR_DIMS (TYPE_2__*) ; 
 void* ARR_LBOUND (TYPE_2__*) ; 
 scalar_t__ ARR_OVERHEAD_WITHNULLS (int,int) ; 
 scalar_t__ ARR_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CopyArrayEls (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ EA_MAGIC ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
EA_flatten_into(ExpandedObjectHeader *eohptr,
				void *result, Size allocated_size)
{
	ExpandedArrayHeader *eah = (ExpandedArrayHeader *) eohptr;
	ArrayType  *aresult = (ArrayType *) result;
	int			nelems;
	int			ndims;
	int32		dataoffset;

	Assert(eah->ea_magic == EA_MAGIC);

	/* Easy if we have a valid flattened value */
	if (eah->fvalue)
	{
		Assert(allocated_size == ARR_SIZE(eah->fvalue));
		memcpy(result, eah->fvalue, allocated_size);
		return;
	}

	/* Else allocation should match previous get_flat_size result */
	Assert(allocated_size == eah->flat_size);

	/* Fill result array from dvalues/dnulls */
	nelems = eah->nelems;
	ndims = eah->ndims;

	if (eah->dnulls)
		dataoffset = ARR_OVERHEAD_WITHNULLS(ndims, nelems);
	else
		dataoffset = 0;			/* marker for no null bitmap */

	/* We must ensure that any pad space is zero-filled */
	memset(aresult, 0, allocated_size);

	SET_VARSIZE(aresult, allocated_size);
	aresult->ndim = ndims;
	aresult->dataoffset = dataoffset;
	aresult->elemtype = eah->element_type;
	memcpy(ARR_DIMS(aresult), eah->dims, ndims * sizeof(int));
	memcpy(ARR_LBOUND(aresult), eah->lbound, ndims * sizeof(int));

	CopyArrayEls(aresult,
				 eah->dvalues, eah->dnulls, nelems,
				 eah->typlen, eah->typbyval, eah->typalign,
				 false);
}
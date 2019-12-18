#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsa_pointer ;
typedef  int /*<<< orphan*/  dsa_area ;
struct TYPE_5__ {void* ptchunks; void* ptpages; void* ptbase; TYPE_1__* state; } ;
struct TYPE_4__ {int /*<<< orphan*/  schunks; scalar_t__ nchunks; int /*<<< orphan*/  spages; scalar_t__ npages; int /*<<< orphan*/  pagetable; } ;
typedef  TYPE_1__ TBMSharedIteratorState ;
typedef  TYPE_2__ TBMSharedIterator ;
typedef  int /*<<< orphan*/  OffsetNumber ;

/* Variables and functions */
 int MAX_TUPLES_PER_PAGE ; 
 void* dsa_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 

TBMSharedIterator *
tbm_attach_shared_iterate(dsa_area *dsa, dsa_pointer dp)
{
	TBMSharedIterator *iterator;
	TBMSharedIteratorState *istate;

	/*
	 * Create the TBMSharedIterator struct, with enough trailing space to
	 * serve the needs of the TBMIterateResult sub-struct.
	 */
	iterator = (TBMSharedIterator *) palloc0(sizeof(TBMSharedIterator) +
											 MAX_TUPLES_PER_PAGE * sizeof(OffsetNumber));

	istate = (TBMSharedIteratorState *) dsa_get_address(dsa, dp);

	iterator->state = istate;

	iterator->ptbase = dsa_get_address(dsa, istate->pagetable);

	if (istate->npages)
		iterator->ptpages = dsa_get_address(dsa, istate->spages);
	if (istate->nchunks)
		iterator->ptchunks = dsa_get_address(dsa, istate->schunks);

	return iterator;
}
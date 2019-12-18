#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pagetable_iterator ;
typedef  void* dsa_pointer ;
struct TYPE_13__ {int /*<<< orphan*/  refcount; TYPE_3__* ptentry; } ;
struct TYPE_12__ {int* index; int /*<<< orphan*/  refcount; } ;
struct TYPE_11__ {scalar_t__ ischunk; } ;
struct TYPE_10__ {int npages; int nchunks; scalar_t__ spageptr; scalar_t__ schunkptr; scalar_t__ schunkbit; int /*<<< orphan*/  lock; void* schunks; void* spages; void* pagetable; int /*<<< orphan*/  maxentries; int /*<<< orphan*/  nentries; } ;
struct TYPE_9__ {scalar_t__ iterating; int npages; int nchunks; scalar_t__ status; void* ptchunks; int /*<<< orphan*/ * dsa; void* ptpages; void* dsapagetable; int /*<<< orphan*/  maxentries; int /*<<< orphan*/  nentries; int /*<<< orphan*/  entry1; int /*<<< orphan*/  pagetable; } ;
typedef  TYPE_1__ TIDBitmap ;
typedef  TYPE_2__ TBMSharedIteratorState ;
typedef  TYPE_3__ PagetableEntry ;
typedef  TYPE_4__ PTIterationArray ;
typedef  TYPE_5__ PTEntryArray ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LWLockInitialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWTRANCHE_TBM ; 
 scalar_t__ TBM_HASH ; 
 scalar_t__ TBM_ITERATING_PRIVATE ; 
 scalar_t__ TBM_ITERATING_SHARED ; 
 scalar_t__ TBM_NOT_ITERATING ; 
 scalar_t__ TBM_ONE_PAGE ; 
 void* dsa_allocate (int /*<<< orphan*/ *,int) ; 
 void* dsa_allocate0 (int /*<<< orphan*/ *,int) ; 
 void* dsa_get_address (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* pagetable_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagetable_start_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_atomic_add_fetch_u32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_atomic_init_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort_arg (void*,int,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tbm_shared_comparator ; 

dsa_pointer
tbm_prepare_shared_iterate(TIDBitmap *tbm)
{
	dsa_pointer dp;
	TBMSharedIteratorState *istate;
	PTEntryArray *ptbase = NULL;
	PTIterationArray *ptpages = NULL;
	PTIterationArray *ptchunks = NULL;

	Assert(tbm->dsa != NULL);
	Assert(tbm->iterating != TBM_ITERATING_PRIVATE);

	/*
	 * Allocate TBMSharedIteratorState from DSA to hold the shared members and
	 * lock, this will also be used by multiple worker for shared iterate.
	 */
	dp = dsa_allocate0(tbm->dsa, sizeof(TBMSharedIteratorState));
	istate = dsa_get_address(tbm->dsa, dp);

	/*
	 * If we're not already iterating, create and fill the sorted page lists.
	 * (If we are, the sorted page lists are already stored in the TIDBitmap,
	 * and we can just reuse them.)
	 */
	if (tbm->iterating == TBM_NOT_ITERATING)
	{
		pagetable_iterator i;
		PagetableEntry *page;
		int			idx;
		int			npages;
		int			nchunks;

		/*
		 * Allocate the page and chunk array memory from the DSA to share
		 * across multiple processes.
		 */
		if (tbm->npages)
		{
			tbm->ptpages = dsa_allocate(tbm->dsa, sizeof(PTIterationArray) +
										tbm->npages * sizeof(int));
			ptpages = dsa_get_address(tbm->dsa, tbm->ptpages);
			pg_atomic_init_u32(&ptpages->refcount, 0);
		}
		if (tbm->nchunks)
		{
			tbm->ptchunks = dsa_allocate(tbm->dsa, sizeof(PTIterationArray) +
										 tbm->nchunks * sizeof(int));
			ptchunks = dsa_get_address(tbm->dsa, tbm->ptchunks);
			pg_atomic_init_u32(&ptchunks->refcount, 0);
		}

		/*
		 * If TBM status is TBM_HASH then iterate over the pagetable and
		 * convert it to page and chunk arrays.  But if it's in the
		 * TBM_ONE_PAGE mode then directly allocate the space for one entry
		 * from the DSA.
		 */
		npages = nchunks = 0;
		if (tbm->status == TBM_HASH)
		{
			ptbase = dsa_get_address(tbm->dsa, tbm->dsapagetable);

			pagetable_start_iterate(tbm->pagetable, &i);
			while ((page = pagetable_iterate(tbm->pagetable, &i)) != NULL)
			{
				idx = page - ptbase->ptentry;
				if (page->ischunk)
					ptchunks->index[nchunks++] = idx;
				else
					ptpages->index[npages++] = idx;
			}

			Assert(npages == tbm->npages);
			Assert(nchunks == tbm->nchunks);
		}
		else if (tbm->status == TBM_ONE_PAGE)
		{
			/*
			 * In one page mode allocate the space for one pagetable entry,
			 * initialize it, and directly store its index (i.e. 0) in the
			 * page array.
			 */
			tbm->dsapagetable = dsa_allocate(tbm->dsa, sizeof(PTEntryArray) +
											 sizeof(PagetableEntry));
			ptbase = dsa_get_address(tbm->dsa, tbm->dsapagetable);
			memcpy(ptbase->ptentry, &tbm->entry1, sizeof(PagetableEntry));
			ptpages->index[0] = 0;
		}

		if (ptbase != NULL)
			pg_atomic_init_u32(&ptbase->refcount, 0);
		if (npages > 1)
			qsort_arg((void *) (ptpages->index), npages, sizeof(int),
					  tbm_shared_comparator, (void *) ptbase->ptentry);
		if (nchunks > 1)
			qsort_arg((void *) (ptchunks->index), nchunks, sizeof(int),
					  tbm_shared_comparator, (void *) ptbase->ptentry);
	}

	/*
	 * Store the TBM members in the shared state so that we can share them
	 * across multiple processes.
	 */
	istate->nentries = tbm->nentries;
	istate->maxentries = tbm->maxentries;
	istate->npages = tbm->npages;
	istate->nchunks = tbm->nchunks;
	istate->pagetable = tbm->dsapagetable;
	istate->spages = tbm->ptpages;
	istate->schunks = tbm->ptchunks;

	ptbase = dsa_get_address(tbm->dsa, tbm->dsapagetable);
	ptpages = dsa_get_address(tbm->dsa, tbm->ptpages);
	ptchunks = dsa_get_address(tbm->dsa, tbm->ptchunks);

	/*
	 * For every shared iterator, referring to pagetable and iterator array,
	 * increase the refcount by 1 so that while freeing the shared iterator we
	 * don't free pagetable and iterator array until its refcount becomes 0.
	 */
	if (ptbase != NULL)
		pg_atomic_add_fetch_u32(&ptbase->refcount, 1);
	if (ptpages != NULL)
		pg_atomic_add_fetch_u32(&ptpages->refcount, 1);
	if (ptchunks != NULL)
		pg_atomic_add_fetch_u32(&ptchunks->refcount, 1);

	/* Initialize the iterator lock */
	LWLockInitialize(&istate->lock, LWTRANCHE_TBM);

	/* Initialize the shared iterator state */
	istate->schunkbit = 0;
	istate->schunkptr = 0;
	istate->spageptr = 0;

	tbm->iterating = TBM_ITERATING_SHARED;

	return dp;
}
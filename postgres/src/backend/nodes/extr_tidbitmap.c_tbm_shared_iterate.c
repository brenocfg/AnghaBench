#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ blockno; int recheck; } ;
struct TYPE_18__ {scalar_t__ blockno; int ntuples; int recheck; } ;
struct TYPE_17__ {TYPE_3__* ptchunks; TYPE_2__* ptpages; TYPE_1__* ptbase; TYPE_4__* state; TYPE_6__ output; } ;
struct TYPE_16__ {size_t schunkptr; size_t nchunks; int schunkbit; size_t spageptr; size_t npages; int /*<<< orphan*/  lock; } ;
struct TYPE_15__ {int* index; } ;
struct TYPE_14__ {int* index; } ;
struct TYPE_13__ {TYPE_7__* ptentry; } ;
typedef  TYPE_4__ TBMSharedIteratorState ;
typedef  TYPE_5__ TBMSharedIterator ;
typedef  TYPE_6__ TBMIterateResult ;
typedef  TYPE_7__ PagetableEntry ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int PAGES_PER_CHUNK ; 
 int /*<<< orphan*/  tbm_advance_schunkbit (TYPE_7__*,int*) ; 
 int tbm_extract_page_tuple (TYPE_7__*,TYPE_6__*) ; 

TBMIterateResult *
tbm_shared_iterate(TBMSharedIterator *iterator)
{
	TBMIterateResult *output = &iterator->output;
	TBMSharedIteratorState *istate = iterator->state;
	PagetableEntry *ptbase = NULL;
	int		   *idxpages = NULL;
	int		   *idxchunks = NULL;

	if (iterator->ptbase != NULL)
		ptbase = iterator->ptbase->ptentry;
	if (iterator->ptpages != NULL)
		idxpages = iterator->ptpages->index;
	if (iterator->ptchunks != NULL)
		idxchunks = iterator->ptchunks->index;

	/* Acquire the LWLock before accessing the shared members */
	LWLockAcquire(&istate->lock, LW_EXCLUSIVE);

	/*
	 * If lossy chunk pages remain, make sure we've advanced schunkptr/
	 * schunkbit to the next set bit.
	 */
	while (istate->schunkptr < istate->nchunks)
	{
		PagetableEntry *chunk = &ptbase[idxchunks[istate->schunkptr]];
		int			schunkbit = istate->schunkbit;

		tbm_advance_schunkbit(chunk, &schunkbit);
		if (schunkbit < PAGES_PER_CHUNK)
		{
			istate->schunkbit = schunkbit;
			break;
		}
		/* advance to next chunk */
		istate->schunkptr++;
		istate->schunkbit = 0;
	}

	/*
	 * If both chunk and per-page data remain, must output the numerically
	 * earlier page.
	 */
	if (istate->schunkptr < istate->nchunks)
	{
		PagetableEntry *chunk = &ptbase[idxchunks[istate->schunkptr]];
		BlockNumber chunk_blockno;

		chunk_blockno = chunk->blockno + istate->schunkbit;

		if (istate->spageptr >= istate->npages ||
			chunk_blockno < ptbase[idxpages[istate->spageptr]].blockno)
		{
			/* Return a lossy page indicator from the chunk */
			output->blockno = chunk_blockno;
			output->ntuples = -1;
			output->recheck = true;
			istate->schunkbit++;

			LWLockRelease(&istate->lock);
			return output;
		}
	}

	if (istate->spageptr < istate->npages)
	{
		PagetableEntry *page = &ptbase[idxpages[istate->spageptr]];
		int			ntuples;

		/* scan bitmap to extract individual offset numbers */
		ntuples = tbm_extract_page_tuple(page, output);
		output->blockno = page->blockno;
		output->ntuples = ntuples;
		output->recheck = page->recheck;
		istate->spageptr++;

		LWLockRelease(&istate->lock);

		return output;
	}

	LWLockRelease(&istate->lock);

	/* Nothing more in the bitmap */
	return NULL;
}
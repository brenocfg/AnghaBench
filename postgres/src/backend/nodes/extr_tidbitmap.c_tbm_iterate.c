#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ blockno; int recheck; } ;
struct TYPE_12__ {scalar_t__ blockno; int ntuples; int recheck; } ;
struct TYPE_11__ {size_t schunkptr; int schunkbit; size_t spageptr; TYPE_3__ output; TYPE_1__* tbm; } ;
struct TYPE_10__ {scalar_t__ iterating; size_t nchunks; size_t npages; scalar_t__ status; TYPE_4__** spages; TYPE_4__ entry1; TYPE_4__** schunks; } ;
typedef  TYPE_1__ TIDBitmap ;
typedef  TYPE_2__ TBMIterator ;
typedef  TYPE_3__ TBMIterateResult ;
typedef  TYPE_4__ PagetableEntry ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int PAGES_PER_CHUNK ; 
 scalar_t__ TBM_ITERATING_PRIVATE ; 
 scalar_t__ TBM_ONE_PAGE ; 
 int /*<<< orphan*/  tbm_advance_schunkbit (TYPE_4__*,int*) ; 
 int tbm_extract_page_tuple (TYPE_4__*,TYPE_3__*) ; 

TBMIterateResult *
tbm_iterate(TBMIterator *iterator)
{
	TIDBitmap  *tbm = iterator->tbm;
	TBMIterateResult *output = &(iterator->output);

	Assert(tbm->iterating == TBM_ITERATING_PRIVATE);

	/*
	 * If lossy chunk pages remain, make sure we've advanced schunkptr/
	 * schunkbit to the next set bit.
	 */
	while (iterator->schunkptr < tbm->nchunks)
	{
		PagetableEntry *chunk = tbm->schunks[iterator->schunkptr];
		int			schunkbit = iterator->schunkbit;

		tbm_advance_schunkbit(chunk, &schunkbit);
		if (schunkbit < PAGES_PER_CHUNK)
		{
			iterator->schunkbit = schunkbit;
			break;
		}
		/* advance to next chunk */
		iterator->schunkptr++;
		iterator->schunkbit = 0;
	}

	/*
	 * If both chunk and per-page data remain, must output the numerically
	 * earlier page.
	 */
	if (iterator->schunkptr < tbm->nchunks)
	{
		PagetableEntry *chunk = tbm->schunks[iterator->schunkptr];
		BlockNumber chunk_blockno;

		chunk_blockno = chunk->blockno + iterator->schunkbit;
		if (iterator->spageptr >= tbm->npages ||
			chunk_blockno < tbm->spages[iterator->spageptr]->blockno)
		{
			/* Return a lossy page indicator from the chunk */
			output->blockno = chunk_blockno;
			output->ntuples = -1;
			output->recheck = true;
			iterator->schunkbit++;
			return output;
		}
	}

	if (iterator->spageptr < tbm->npages)
	{
		PagetableEntry *page;
		int			ntuples;

		/* In TBM_ONE_PAGE state, we don't allocate an spages[] array */
		if (tbm->status == TBM_ONE_PAGE)
			page = &tbm->entry1;
		else
			page = tbm->spages[iterator->spageptr];

		/* scan bitmap to extract individual offset numbers */
		ntuples = tbm_extract_page_tuple(page, output);
		output->blockno = page->blockno;
		output->ntuples = ntuples;
		output->recheck = page->recheck;
		iterator->spageptr++;
		return output;
	}

	/* Nothing more in the bitmap */
	return NULL;
}
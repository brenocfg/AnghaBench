#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int bloomLength; } ;
struct TYPE_14__ {scalar_t__ magickNumber; int /*<<< orphan*/  opts; } ;
struct TYPE_13__ {int nColumns; TYPE_5__ opts; scalar_t__ sizeOfBloomTuple; int /*<<< orphan*/ * collations; int /*<<< orphan*/ * hashFn; } ;
struct TYPE_12__ {void* rd_amcache; int /*<<< orphan*/  rd_indexcxt; int /*<<< orphan*/ * rd_indcollation; TYPE_1__* rd_att; } ;
struct TYPE_11__ {int natts; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_3__ BloomState ;
typedef  int /*<<< orphan*/  BloomSignatureWord ;
typedef  int /*<<< orphan*/  BloomOptions ;
typedef  TYPE_4__ BloomMetaPageData ;

/* Variables and functions */
 scalar_t__ BLOOMTUPLEHDRSZ ; 
 int /*<<< orphan*/  BLOOM_HASH_PROC ; 
 scalar_t__ BLOOM_MAGICK_NUMBER ; 
 int /*<<< orphan*/  BLOOM_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 TYPE_4__* BloomPageGetMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BloomPageIsMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReadBuffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fmgr_info_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getprocinfo (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,void*,int) ; 

void
initBloomState(BloomState *state, Relation index)
{
	int			i;

	state->nColumns = index->rd_att->natts;

	/* Initialize hash function for each attribute */
	for (i = 0; i < index->rd_att->natts; i++)
	{
		fmgr_info_copy(&(state->hashFn[i]),
					   index_getprocinfo(index, i + 1, BLOOM_HASH_PROC),
					   CurrentMemoryContext);
		state->collations[i] = index->rd_indcollation[i];
	}

	/* Initialize amcache if needed with options from metapage */
	if (!index->rd_amcache)
	{
		Buffer		buffer;
		Page		page;
		BloomMetaPageData *meta;
		BloomOptions *opts;

		opts = MemoryContextAlloc(index->rd_indexcxt, sizeof(BloomOptions));

		buffer = ReadBuffer(index, BLOOM_METAPAGE_BLKNO);
		LockBuffer(buffer, BUFFER_LOCK_SHARE);

		page = BufferGetPage(buffer);

		if (!BloomPageIsMeta(page))
			elog(ERROR, "Relation is not a bloom index");
		meta = BloomPageGetMeta(BufferGetPage(buffer));

		if (meta->magickNumber != BLOOM_MAGICK_NUMBER)
			elog(ERROR, "Relation is not a bloom index");

		*opts = meta->opts;

		UnlockReleaseBuffer(buffer);

		index->rd_amcache = (void *) opts;
	}

	memcpy(&state->opts, index->rd_amcache, sizeof(state->opts));
	state->sizeOfBloomTuple = BLOOMTUPLEHDRSZ +
		sizeof(BloomSignatureWord) * state->opts.bloomLength;
}
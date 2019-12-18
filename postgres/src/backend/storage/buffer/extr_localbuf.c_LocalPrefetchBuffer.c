#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
struct TYPE_6__ {TYPE_1__ smgr_rnode; } ;
typedef  TYPE_2__* SMgrRelation ;
typedef  int /*<<< orphan*/  LocalBufferLookupEnt ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  int /*<<< orphan*/  BufferTag ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  INIT_BUFFERTAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitLocalBuffers () ; 
 int /*<<< orphan*/ * LocalBufHash ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smgrprefetch (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
LocalPrefetchBuffer(SMgrRelation smgr, ForkNumber forkNum,
					BlockNumber blockNum)
{
#ifdef USE_PREFETCH
	BufferTag	newTag;			/* identity of requested block */
	LocalBufferLookupEnt *hresult;

	INIT_BUFFERTAG(newTag, smgr->smgr_rnode.node, forkNum, blockNum);

	/* Initialize local buffers if first request in this session */
	if (LocalBufHash == NULL)
		InitLocalBuffers();

	/* See if the desired buffer already exists */
	hresult = (LocalBufferLookupEnt *)
		hash_search(LocalBufHash, (void *) &newTag, HASH_FIND, NULL);

	if (hresult)
	{
		/* Yes, so nothing to do */
		return;
	}

	/* Not in buffers, so initiate prefetch */
	smgrprefetch(smgr, forkNum, blockNum);
#endif							/* USE_PREFETCH */
}
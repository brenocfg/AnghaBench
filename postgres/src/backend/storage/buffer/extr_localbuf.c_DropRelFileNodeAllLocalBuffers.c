#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_5__ {int /*<<< orphan*/  forkNum; int /*<<< orphan*/  rnode; int /*<<< orphan*/  blockNum; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; TYPE_3__ tag; } ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  int /*<<< orphan*/  LocalBufferLookupEnt ;
typedef  TYPE_1__ BufferDesc ;

/* Variables and functions */
 int BM_TAG_VALID ; 
 int BUF_FLAG_MASK ; 
 int BUF_USAGECOUNT_MASK ; 
 int /*<<< orphan*/  CLEAR_BUFFERTAG (TYPE_3__) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* GetLocalBufferDescriptor (int) ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  LocalBufHash ; 
 scalar_t__* LocalRefCount ; 
 int /*<<< orphan*/  MyBackendId ; 
 int NLocBuffer ; 
 scalar_t__ RelFileNodeEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_atomic_unlocked_write_u32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  relpathbackend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
DropRelFileNodeAllLocalBuffers(RelFileNode rnode)
{
	int			i;

	for (i = 0; i < NLocBuffer; i++)
	{
		BufferDesc *bufHdr = GetLocalBufferDescriptor(i);
		LocalBufferLookupEnt *hresult;
		uint32		buf_state;

		buf_state = pg_atomic_read_u32(&bufHdr->state);

		if ((buf_state & BM_TAG_VALID) &&
			RelFileNodeEquals(bufHdr->tag.rnode, rnode))
		{
			if (LocalRefCount[i] != 0)
				elog(ERROR, "block %u of %s is still referenced (local %u)",
					 bufHdr->tag.blockNum,
					 relpathbackend(bufHdr->tag.rnode, MyBackendId,
									bufHdr->tag.forkNum),
					 LocalRefCount[i]);
			/* Remove entry from hashtable */
			hresult = (LocalBufferLookupEnt *)
				hash_search(LocalBufHash, (void *) &bufHdr->tag,
							HASH_REMOVE, NULL);
			if (!hresult)		/* shouldn't happen */
				elog(ERROR, "local buffer hash table corrupted");
			/* Mark buffer invalid */
			CLEAR_BUFFERTAG(bufHdr->tag);
			buf_state &= ~BUF_FLAG_MASK;
			buf_state &= ~BUF_USAGECOUNT_MASK;
			pg_atomic_unlocked_write_u32(&bufHdr->state, buf_state);
		}
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_18__ {int /*<<< orphan*/  rnode; int /*<<< orphan*/  blockNum; int /*<<< orphan*/  forkNum; } ;
struct TYPE_21__ {TYPE_1__ tag; int /*<<< orphan*/  state; } ;
struct TYPE_20__ {struct TYPE_20__* previous; void* arg; int /*<<< orphan*/  callback; } ;
struct TYPE_19__ {int /*<<< orphan*/  rd_smgr; int /*<<< orphan*/  rd_node; } ;
typedef  TYPE_2__* Relation ;
typedef  char* Page ;
typedef  TYPE_3__ ErrorContextCallback ;
typedef  TYPE_4__ BufferDesc ;

/* Variables and functions */
 int BM_DIRTY ; 
 int BM_JUST_DIRTIED ; 
 int BM_VALID ; 
 int /*<<< orphan*/  BufferDescriptorGetContentLock (TYPE_4__*) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  FlushBuffer (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* GetBufferDescriptor (int) ; 
 TYPE_4__* GetLocalBufferDescriptor (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 scalar_t__ LocalBufHdrGetBlock (TYPE_4__*) ; 
 int LockBufHdr (TYPE_4__*) ; 
 int NBuffers ; 
 int NLocBuffer ; 
 int /*<<< orphan*/  PageSetChecksumInplace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PinBuffer_Locked (TYPE_4__*) ; 
 scalar_t__ RelFileNodeEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_2__*) ; 
 scalar_t__ RelationUsesLocalBuffers (TYPE_2__*) ; 
 int /*<<< orphan*/  ReservePrivateRefCountEntry () ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_4__*,int) ; 
 int /*<<< orphan*/  UnpinBuffer (TYPE_4__*,int) ; 
 TYPE_3__* error_context_stack ; 
 int /*<<< orphan*/  local_buffer_write_error_callback ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_atomic_unlocked_write_u32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smgrwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void
FlushRelationBuffers(Relation rel)
{
	int			i;
	BufferDesc *bufHdr;

	/* Open rel at the smgr level if not already done */
	RelationOpenSmgr(rel);

	if (RelationUsesLocalBuffers(rel))
	{
		for (i = 0; i < NLocBuffer; i++)
		{
			uint32		buf_state;

			bufHdr = GetLocalBufferDescriptor(i);
			if (RelFileNodeEquals(bufHdr->tag.rnode, rel->rd_node) &&
				((buf_state = pg_atomic_read_u32(&bufHdr->state)) &
				 (BM_VALID | BM_DIRTY)) == (BM_VALID | BM_DIRTY))
			{
				ErrorContextCallback errcallback;
				Page		localpage;

				localpage = (char *) LocalBufHdrGetBlock(bufHdr);

				/* Setup error traceback support for ereport() */
				errcallback.callback = local_buffer_write_error_callback;
				errcallback.arg = (void *) bufHdr;
				errcallback.previous = error_context_stack;
				error_context_stack = &errcallback;

				PageSetChecksumInplace(localpage, bufHdr->tag.blockNum);

				smgrwrite(rel->rd_smgr,
						  bufHdr->tag.forkNum,
						  bufHdr->tag.blockNum,
						  localpage,
						  false);

				buf_state &= ~(BM_DIRTY | BM_JUST_DIRTIED);
				pg_atomic_unlocked_write_u32(&bufHdr->state, buf_state);

				/* Pop the error context stack */
				error_context_stack = errcallback.previous;
			}
		}

		return;
	}

	/* Make sure we can handle the pin inside the loop */
	ResourceOwnerEnlargeBuffers(CurrentResourceOwner);

	for (i = 0; i < NBuffers; i++)
	{
		uint32		buf_state;

		bufHdr = GetBufferDescriptor(i);

		/*
		 * As in DropRelFileNodeBuffers, an unlocked precheck should be safe
		 * and saves some cycles.
		 */
		if (!RelFileNodeEquals(bufHdr->tag.rnode, rel->rd_node))
			continue;

		ReservePrivateRefCountEntry();

		buf_state = LockBufHdr(bufHdr);
		if (RelFileNodeEquals(bufHdr->tag.rnode, rel->rd_node) &&
			(buf_state & (BM_VALID | BM_DIRTY)) == (BM_VALID | BM_DIRTY))
		{
			PinBuffer_Locked(bufHdr);
			LWLockAcquire(BufferDescriptorGetContentLock(bufHdr), LW_SHARED);
			FlushBuffer(bufHdr, rel->rd_smgr);
			LWLockRelease(BufferDescriptorGetContentLock(bufHdr));
			UnpinBuffer(bufHdr, true);
		}
		else
			UnlockBufHdr(bufHdr, buf_state);
	}
}
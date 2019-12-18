#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int buf_id; int freeNext; scalar_t__ wait_backend_pid; int /*<<< orphan*/  state; int /*<<< orphan*/  tag; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  LWLockMinimallyPadded ;
typedef  int /*<<< orphan*/  CkptSortItem ;
typedef  int /*<<< orphan*/  BufferDescPadded ;
typedef  TYPE_1__ BufferDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  BackendWritebackContext ; 
 char* BufferBlocks ; 
 int /*<<< orphan*/  BufferDescriptorGetContentLock (TYPE_1__*) ; 
 int /*<<< orphan*/  BufferDescriptorGetIOLock (TYPE_1__*) ; 
 int /*<<< orphan*/ * BufferDescriptors ; 
 int /*<<< orphan*/ * BufferIOLWLockArray ; 
 int /*<<< orphan*/  CLEAR_BUFFERTAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CkptBufferIds ; 
 int FREENEXT_END_OF_LIST ; 
 TYPE_1__* GetBufferDescriptor (int) ; 
 int /*<<< orphan*/  LWLockInitialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRegisterTranche (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWTRANCHE_BUFFER_CONTENT ; 
 int /*<<< orphan*/  LWTRANCHE_BUFFER_IO_IN_PROGRESS ; 
 int NBuffers ; 
 scalar_t__ ShmemInitStruct (char*,int,int*) ; 
 int /*<<< orphan*/  StrategyInitialize (int) ; 
 int /*<<< orphan*/  WritebackContextInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backend_flush_after ; 
 int /*<<< orphan*/  pg_atomic_init_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
InitBufferPool(void)
{
	bool		foundBufs,
				foundDescs,
				foundIOLocks,
				foundBufCkpt;

	/* Align descriptors to a cacheline boundary. */
	BufferDescriptors = (BufferDescPadded *)
		ShmemInitStruct("Buffer Descriptors",
						NBuffers * sizeof(BufferDescPadded),
						&foundDescs);

	BufferBlocks = (char *)
		ShmemInitStruct("Buffer Blocks",
						NBuffers * (Size) BLCKSZ, &foundBufs);

	/* Align lwlocks to cacheline boundary */
	BufferIOLWLockArray = (LWLockMinimallyPadded *)
		ShmemInitStruct("Buffer IO Locks",
						NBuffers * (Size) sizeof(LWLockMinimallyPadded),
						&foundIOLocks);

	LWLockRegisterTranche(LWTRANCHE_BUFFER_IO_IN_PROGRESS, "buffer_io");
	LWLockRegisterTranche(LWTRANCHE_BUFFER_CONTENT, "buffer_content");

	/*
	 * The array used to sort to-be-checkpointed buffer ids is located in
	 * shared memory, to avoid having to allocate significant amounts of
	 * memory at runtime. As that'd be in the middle of a checkpoint, or when
	 * the checkpointer is restarted, memory allocation failures would be
	 * painful.
	 */
	CkptBufferIds = (CkptSortItem *)
		ShmemInitStruct("Checkpoint BufferIds",
						NBuffers * sizeof(CkptSortItem), &foundBufCkpt);

	if (foundDescs || foundBufs || foundIOLocks || foundBufCkpt)
	{
		/* should find all of these, or none of them */
		Assert(foundDescs && foundBufs && foundIOLocks && foundBufCkpt);
		/* note: this path is only taken in EXEC_BACKEND case */
	}
	else
	{
		int			i;

		/*
		 * Initialize all the buffer headers.
		 */
		for (i = 0; i < NBuffers; i++)
		{
			BufferDesc *buf = GetBufferDescriptor(i);

			CLEAR_BUFFERTAG(buf->tag);

			pg_atomic_init_u32(&buf->state, 0);
			buf->wait_backend_pid = 0;

			buf->buf_id = i;

			/*
			 * Initially link all the buffers together as unused. Subsequent
			 * management of this list is done by freelist.c.
			 */
			buf->freeNext = i + 1;

			LWLockInitialize(BufferDescriptorGetContentLock(buf),
							 LWTRANCHE_BUFFER_CONTENT);

			LWLockInitialize(BufferDescriptorGetIOLock(buf),
							 LWTRANCHE_BUFFER_IO_IN_PROGRESS);
		}

		/* Correct last entry of linked list */
		GetBufferDescriptor(NBuffers - 1)->freeNext = FREENEXT_END_OF_LIST;
	}

	/* Init other shared buffer-management stuff */
	StrategyInitialize(!foundDescs);

	/* Initialize per-backend file flush context */
	WritebackContextInit(&BackendWritebackContext,
						 &backend_flush_after);
}
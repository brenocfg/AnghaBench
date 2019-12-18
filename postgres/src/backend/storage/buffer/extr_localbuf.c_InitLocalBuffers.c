#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_8__ {int buf_id; } ;
struct TYPE_7__ {int keysize; int entrysize; } ;
typedef  int /*<<< orphan*/  LocalBufferLookupEnt ;
typedef  TYPE_1__ HASHCTL ;
typedef  int /*<<< orphan*/  BufferTag ;
typedef  TYPE_2__ BufferDesc ;
typedef  int /*<<< orphan*/  Block ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TRANSACTION_STATE ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 TYPE_2__* GetLocalBufferDescriptor (int) ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 scalar_t__ IsParallelWorker () ; 
 int /*<<< orphan*/  LocalBufHash ; 
 int /*<<< orphan*/ * LocalBufferBlockPointers ; 
 TYPE_2__* LocalBufferDescriptors ; 
 int /*<<< orphan*/ * LocalRefCount ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int NLocBuffer ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_1__*,int) ; 
 scalar_t__ nextFreeLocalBuf ; 
 int num_temp_buffers ; 

__attribute__((used)) static void
InitLocalBuffers(void)
{
	int			nbufs = num_temp_buffers;
	HASHCTL		info;
	int			i;

	/*
	 * Parallel workers can't access data in temporary tables, because they
	 * have no visibility into the local buffers of their leader.  This is a
	 * convenient, low-cost place to provide a backstop check for that.  Note
	 * that we don't wish to prevent a parallel worker from accessing catalog
	 * metadata about a temp table, so checks at higher levels would be
	 * inappropriate.
	 */
	if (IsParallelWorker())
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TRANSACTION_STATE),
				 errmsg("cannot access temporary tables during a parallel operation")));

	/* Allocate and zero buffer headers and auxiliary arrays */
	LocalBufferDescriptors = (BufferDesc *) calloc(nbufs, sizeof(BufferDesc));
	LocalBufferBlockPointers = (Block *) calloc(nbufs, sizeof(Block));
	LocalRefCount = (int32 *) calloc(nbufs, sizeof(int32));
	if (!LocalBufferDescriptors || !LocalBufferBlockPointers || !LocalRefCount)
		ereport(FATAL,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory")));

	nextFreeLocalBuf = 0;

	/* initialize fields that need to start off nonzero */
	for (i = 0; i < nbufs; i++)
	{
		BufferDesc *buf = GetLocalBufferDescriptor(i);

		/*
		 * negative to indicate local buffer. This is tricky: shared buffers
		 * start with 0. We have to start with -2. (Note that the routine
		 * BufferDescriptorGetBuffer adds 1 to buf_id so our first buffer id
		 * is -1.)
		 */
		buf->buf_id = -i - 2;

		/*
		 * Intentionally do not initialize the buffer's atomic variable
		 * (besides zeroing the underlying memory above). That way we get
		 * errors on platforms without atomics, if somebody (re-)introduces
		 * atomic operations for local buffers.
		 */
	}

	/* Create the lookup hash table */
	MemSet(&info, 0, sizeof(info));
	info.keysize = sizeof(BufferTag);
	info.entrysize = sizeof(LocalBufferLookupEnt);

	LocalBufHash = hash_create("Local Buffer Lookup Table",
							   nbufs,
							   &info,
							   HASH_ELEM | HASH_BLOBS);

	if (!LocalBufHash)
		elog(ERROR, "could not initialize local buffer hash table");

	/* Initialization done, mark buffers allocated */
	NLocBuffer = nbufs;
}
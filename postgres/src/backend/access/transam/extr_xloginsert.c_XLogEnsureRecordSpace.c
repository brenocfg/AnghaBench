#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  registered_buffer ;
typedef  int /*<<< orphan*/  XLogRecData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CritSectionCount ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int XLR_MAX_BLOCK_ID ; 
 int XLR_NORMAL_MAX_BLOCK_ID ; 
 int XLR_NORMAL_RDATAS ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int max_rdatas ; 
 int max_registered_buffers ; 
 int /*<<< orphan*/ * rdatas ; 
 int /*<<< orphan*/ * registered_buffers ; 
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 

void
XLogEnsureRecordSpace(int max_block_id, int ndatas)
{
	int			nbuffers;

	/*
	 * This must be called before entering a critical section, because
	 * allocating memory inside a critical section can fail. repalloc() will
	 * check the same, but better to check it here too so that we fail
	 * consistently even if the arrays happen to be large enough already.
	 */
	Assert(CritSectionCount == 0);

	/* the minimum values can't be decreased */
	if (max_block_id < XLR_NORMAL_MAX_BLOCK_ID)
		max_block_id = XLR_NORMAL_MAX_BLOCK_ID;
	if (ndatas < XLR_NORMAL_RDATAS)
		ndatas = XLR_NORMAL_RDATAS;

	if (max_block_id > XLR_MAX_BLOCK_ID)
		elog(ERROR, "maximum number of WAL record block references exceeded");
	nbuffers = max_block_id + 1;

	if (nbuffers > max_registered_buffers)
	{
		registered_buffers = (registered_buffer *)
			repalloc(registered_buffers, sizeof(registered_buffer) * nbuffers);

		/*
		 * At least the padding bytes in the structs must be zeroed, because
		 * they are included in WAL data, but initialize it all for tidiness.
		 */
		MemSet(&registered_buffers[max_registered_buffers], 0,
			   (nbuffers - max_registered_buffers) * sizeof(registered_buffer));
		max_registered_buffers = nbuffers;
	}

	if (ndatas > max_rdatas)
	{
		rdatas = (XLogRecData *) repalloc(rdatas, sizeof(XLogRecData) * ndatas);
		max_rdatas = ndatas;
	}
}
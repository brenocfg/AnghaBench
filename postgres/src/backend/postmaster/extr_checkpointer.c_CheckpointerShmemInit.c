#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  done_cv; int /*<<< orphan*/  start_cv; int /*<<< orphan*/  max_requests; int /*<<< orphan*/  ckpt_lck; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_1__ CheckpointerShmemStruct ;

/* Variables and functions */
 TYPE_1__* CheckpointerShmem ; 
 int /*<<< orphan*/  CheckpointerShmemSize () ; 
 int /*<<< orphan*/  ConditionVariableInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBuffers ; 
 scalar_t__ ShmemInitStruct (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 

void
CheckpointerShmemInit(void)
{
	Size		size = CheckpointerShmemSize();
	bool		found;

	CheckpointerShmem = (CheckpointerShmemStruct *)
		ShmemInitStruct("Checkpointer Data",
						size,
						&found);

	if (!found)
	{
		/*
		 * First time through, so initialize.  Note that we zero the whole
		 * requests array; this is so that CompactCheckpointerRequestQueue can
		 * assume that any pad bytes in the request structs are zeroes.
		 */
		MemSet(CheckpointerShmem, 0, size);
		SpinLockInit(&CheckpointerShmem->ckpt_lck);
		CheckpointerShmem->max_requests = NBuffers;
		ConditionVariableInit(&CheckpointerShmem->start_cv);
		ConditionVariableInit(&CheckpointerShmem->done_cv);
	}
}
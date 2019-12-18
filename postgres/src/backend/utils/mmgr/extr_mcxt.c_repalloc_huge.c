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
struct TYPE_8__ {int /*<<< orphan*/  name; TYPE_1__* methods; int /*<<< orphan*/  isReset; } ;
struct TYPE_7__ {void* (* realloc ) (TYPE_2__*,void*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__* MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  AllocHugeSizeIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertNotInCriticalSection (TYPE_2__*) ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* GetMemoryChunkContext (void*) ; 
 int /*<<< orphan*/  MemoryContextStats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  VALGRIND_MEMPOOL_CHANGE (TYPE_2__*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 void* stub1 (TYPE_2__*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void *
repalloc_huge(void *pointer, Size size)
{
	MemoryContext context = GetMemoryChunkContext(pointer);
	void	   *ret;

	if (!AllocHugeSizeIsValid(size))
		elog(ERROR, "invalid memory alloc request size %zu", size);

	AssertNotInCriticalSection(context);

	/* isReset must be false already */
	Assert(!context->isReset);

	ret = context->methods->realloc(context, pointer, size);
	if (unlikely(ret == NULL))
	{
		MemoryContextStats(TopMemoryContext);
		ereport(ERROR,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory"),
				 errdetail("Failed on request of size %zu in memory context \"%s\".",
						   size, context->name)));
	}

	VALGRIND_MEMPOOL_CHANGE(context, pointer, ret, size);

	return ret;
}
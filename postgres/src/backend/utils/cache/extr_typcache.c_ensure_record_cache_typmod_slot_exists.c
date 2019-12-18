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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;

/* Variables and functions */
 int /*<<< orphan*/  CacheMemoryContext ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * RecordCacheArray ; 
 int RecordCacheArrayLen ; 
 int /*<<< orphan*/ * RecordIdentifierArray ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ensure_record_cache_typmod_slot_exists(int32 typmod)
{
	if (RecordCacheArray == NULL)
	{
		RecordCacheArray = (TupleDesc *)
			MemoryContextAllocZero(CacheMemoryContext, 64 * sizeof(TupleDesc));
		RecordIdentifierArray = (uint64 *)
			MemoryContextAllocZero(CacheMemoryContext, 64 * sizeof(uint64));
		RecordCacheArrayLen = 64;
	}

	if (typmod >= RecordCacheArrayLen)
	{
		int32		newlen = RecordCacheArrayLen * 2;

		while (typmod >= newlen)
			newlen *= 2;

		RecordCacheArray = (TupleDesc *) repalloc(RecordCacheArray,
												  newlen * sizeof(TupleDesc));
		memset(RecordCacheArray + RecordCacheArrayLen, 0,
			   (newlen - RecordCacheArrayLen) * sizeof(TupleDesc));
		RecordIdentifierArray = (uint64 *) repalloc(RecordIdentifierArray,
													newlen * sizeof(uint64));
		memset(RecordIdentifierArray + RecordCacheArrayLen, 0,
			   (newlen - RecordCacheArrayLen) * sizeof(uint64));
		RecordCacheArrayLen = newlen;
	}
}
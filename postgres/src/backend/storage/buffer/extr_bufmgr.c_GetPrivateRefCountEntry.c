#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ buffer; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ PrivateRefCountEntry ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferIsLocal (scalar_t__) ; 
 int BufferIsValid (scalar_t__) ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 scalar_t__ InvalidBuffer ; 
 TYPE_1__* PrivateRefCountArray ; 
 int /*<<< orphan*/  PrivateRefCountHash ; 
 scalar_t__ PrivateRefCountOverflowed ; 
 int REFCOUNT_ARRAY_ENTRIES ; 
 int /*<<< orphan*/  ReservePrivateRefCountEntry () ; 
 TYPE_1__* ReservedRefCountEntry ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static PrivateRefCountEntry *
GetPrivateRefCountEntry(Buffer buffer, bool do_move)
{
	PrivateRefCountEntry *res;
	int			i;

	Assert(BufferIsValid(buffer));
	Assert(!BufferIsLocal(buffer));

	/*
	 * First search for references in the array, that'll be sufficient in the
	 * majority of cases.
	 */
	for (i = 0; i < REFCOUNT_ARRAY_ENTRIES; i++)
	{
		res = &PrivateRefCountArray[i];

		if (res->buffer == buffer)
			return res;
	}

	/*
	 * By here we know that the buffer, if already pinned, isn't residing in
	 * the array.
	 *
	 * Only look up the buffer in the hashtable if we've previously overflowed
	 * into it.
	 */
	if (PrivateRefCountOverflowed == 0)
		return NULL;

	res = hash_search(PrivateRefCountHash,
					  (void *) &buffer,
					  HASH_FIND,
					  NULL);

	if (res == NULL)
		return NULL;
	else if (!do_move)
	{
		/* caller doesn't want us to move the hash entry into the array */
		return res;
	}
	else
	{
		/* move buffer from hashtable into the free array slot */
		bool		found;
		PrivateRefCountEntry *free;

		/* Ensure there's a free array slot */
		ReservePrivateRefCountEntry();

		/* Use up the reserved slot */
		Assert(ReservedRefCountEntry != NULL);
		free = ReservedRefCountEntry;
		ReservedRefCountEntry = NULL;
		Assert(free->buffer == InvalidBuffer);

		/* and fill it */
		free->buffer = buffer;
		free->refcount = res->refcount;

		/* delete from hashtable */
		hash_search(PrivateRefCountHash,
					(void *) &buffer,
					HASH_REMOVE,
					&found);
		Assert(found);
		Assert(PrivateRefCountOverflowed > 0);
		PrivateRefCountOverflowed--;

		return free;
	}
}
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
struct TYPE_5__ {scalar_t__ refcount; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ PrivateRefCountEntry ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 TYPE_1__* PrivateRefCountArray ; 
 int /*<<< orphan*/  PrivateRefCountHash ; 
 scalar_t__ PrivateRefCountOverflowed ; 
 size_t REFCOUNT_ARRAY_ENTRIES ; 
 TYPE_1__* ReservedRefCountEntry ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
ForgetPrivateRefCountEntry(PrivateRefCountEntry *ref)
{
	Assert(ref->refcount == 0);

	if (ref >= &PrivateRefCountArray[0] &&
		ref < &PrivateRefCountArray[REFCOUNT_ARRAY_ENTRIES])
	{
		ref->buffer = InvalidBuffer;

		/*
		 * Mark the just used entry as reserved - in many scenarios that
		 * allows us to avoid ever having to search the array/hash for free
		 * entries.
		 */
		ReservedRefCountEntry = ref;
	}
	else
	{
		bool		found;
		Buffer		buffer = ref->buffer;

		hash_search(PrivateRefCountHash,
					(void *) &buffer,
					HASH_REMOVE,
					&found);
		Assert(found);
		Assert(PrivateRefCountOverflowed > 0);
		PrivateRefCountOverflowed--;
	}
}
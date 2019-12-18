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
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ EstimateEnumBlacklistSpace () ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ enum_blacklist ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

void
SerializeEnumBlacklist(void *space, Size size)
{
	Oid		   *serialized = (Oid *) space;

	/*
	 * Make sure the hash table hasn't changed in size since the caller
	 * reserved the space.
	 */
	Assert(size == EstimateEnumBlacklistSpace());

	/* Write out all the values from the hash table, if there is one. */
	if (enum_blacklist)
	{
		HASH_SEQ_STATUS status;
		Oid		   *value;

		hash_seq_init(&status, enum_blacklist);
		while ((value = (Oid *) hash_seq_search(&status)))
			*serialized++ = *value;
	}

	/* Write out the terminator. */
	*serialized = InvalidOid;

	/*
	 * Make sure the amount of space we actually used matches what was
	 * estimated.
	 */
	Assert((char *) (serialized + 1) == ((char *) space) + size);
}
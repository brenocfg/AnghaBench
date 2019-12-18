#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ relid; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ RelfilenodeMapEntry ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/ * RelfilenodeMapHash ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
RelfilenodeMapInvalidateCallback(Datum arg, Oid relid)
{
	HASH_SEQ_STATUS status;
	RelfilenodeMapEntry *entry;

	/* callback only gets registered after creating the hash */
	Assert(RelfilenodeMapHash != NULL);

	hash_seq_init(&status, RelfilenodeMapHash);
	while ((entry = (RelfilenodeMapEntry *) hash_seq_search(&status)) != NULL)
	{
		/*
		 * If relid is InvalidOid, signalling a complete reset, we must remove
		 * all entries, otherwise just remove the specific relation's entry.
		 * Always remove negative cache entries.
		 */
		if (relid == InvalidOid ||	/* complete reset */
			entry->relid == InvalidOid ||	/* negative cache entry */
			entry->relid == relid)	/* individual flushed relation */
		{
			if (hash_search(RelfilenodeMapHash,
							(void *) &entry->key,
							HASH_REMOVE,
							NULL) == NULL)
				elog(ERROR, "hash table corrupted");
		}
	}
}
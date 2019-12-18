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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ OprCacheEntry ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/ * OprCacheHash ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
InvalidateOprCacheCallBack(Datum arg, int cacheid, uint32 hashvalue)
{
	HASH_SEQ_STATUS status;
	OprCacheEntry *hentry;

	Assert(OprCacheHash != NULL);

	/* Currently we just flush all entries; hard to be smarter ... */
	hash_seq_init(&status, OprCacheHash);

	while ((hentry = (OprCacheEntry *) hash_seq_search(&status)) != NULL)
	{
		if (hash_search(OprCacheHash,
						(void *) &hentry->key,
						HASH_REMOVE, NULL) == NULL)
			elog(ERROR, "hash table corrupted");
	}
}
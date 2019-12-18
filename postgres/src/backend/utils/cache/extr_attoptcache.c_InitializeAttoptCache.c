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
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_4__ {int keysize; int entrysize; } ;
typedef  TYPE_1__ HASHCTL ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttoptCacheKey ;
typedef  int /*<<< orphan*/  AttoptCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 int /*<<< orphan*/  AttoptCacheHash ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  CacheRegisterSyscacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCacheMemoryContext () ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  InvalidateAttoptCacheCallback ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_1__*,int) ; 

__attribute__((used)) static void
InitializeAttoptCache(void)
{
	HASHCTL		ctl;

	/* Initialize the hash table. */
	MemSet(&ctl, 0, sizeof(ctl));
	ctl.keysize = sizeof(AttoptCacheKey);
	ctl.entrysize = sizeof(AttoptCacheEntry);
	AttoptCacheHash =
		hash_create("Attopt cache", 256, &ctl,
					HASH_ELEM | HASH_BLOBS);

	/* Make sure we've initialized CacheMemoryContext. */
	if (!CacheMemoryContext)
		CreateCacheMemoryContext();

	/* Watch for invalidation events. */
	CacheRegisterSyscacheCallback(ATTNUM,
								  InvalidateAttoptCacheCallback,
								  (Datum) 0);
}